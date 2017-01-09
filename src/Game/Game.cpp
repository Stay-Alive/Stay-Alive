#include "Game.hpp"
#include <string>
#include <math.h>
using namespace std;

Game::Game()
{
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        return;
    }
    display = new Display();
    glewExperimental = GL_TRUE;
    // Initialize GLEW
	if (glewInit() != GLEW_OK)
    {
		cerr << "Failed to initialize GLEW\n";
	}
    // initialize game status
    life = 10;
    gameState = GAME_START;
    isTimeFrozen = false;
}

Game::~Game()
{
    delete display;
    glfwTerminate();
}

void Game::Start()
{
    cerr << "Game started\n";
    this->gameState = GAME_RUNNING;
    this->life = 10;
    this->stone = 0;
    this->wood = 0;

    Loader loader;
    srand(time(NULL));  // initialize random number generation

    //sky
    SkyRenderer skyRenderer(loader.LoadTexture("sky"));
//    skyRenderer.Render(0.95);

    // terrain
    vector<Terrain> terrains;
    ModelTexture mtGrass2(loader.LoadTexture("grassy", true));
    terrains.push_back(Terrain(loader, mtGrass2));
    Terrain& theTerrain = terrains[0];  // so that we can get altitude from it

    // entities
    vector<Entity> entities;
    vector<RawModel *> rawModels;
    // add entities, encapsulate this part in a function to make Start() shorter
    BuildWorld(loader, entities, theTerrain, rawModels);

    // light
    glm::vec3 colorWhite(1.0, 1.0, 1.0);
    glm::vec3 colorBlack(0.0,0.0,0.0);
    glm::vec3 lightPosition(0.0, LIGHT_HEIGHT, 0.0);
    glm::vec3 nightPosition(0.0,2.0,0.0);
    SimpleLight light(lightPosition, colorWhite);

    //ClockTime
    ClockTime MyCLock;

    Camera camera;
    Renderer renderer(display->GetAspect());
    TextRenderer textRenderer(loader.LoadTexture("font"));

    // variables for game state
    int currentDay;
    int previousHour = 12, currentHour;
    double PreciseTime=0.5;
    double previousTimeSpacePressed = 0, currentTimeSpacePressed;
    while(!display->IsWindowClosed())
    {
        GLfloat altitude = 0.0f;
        GLfloat cameraX = camera.GetPosition().x;
        GLfloat cameraZ = camera.GetPosition().z;
        if (cameraZ > -0.5 * TERRAIN_SIZE && cameraZ < 0.5 * TERRAIN_SIZE && cameraX > -0.5 * TERRAIN_SIZE && cameraX < 0.5 * TERRAIN_SIZE)  // if we are inside the terrain
        {
            altitude = theTerrain.GetAltitudeAt(cameraX, cameraZ);
        }

        //skyRenderer.Render(PreciseTime);

        //
        if (GAME_OVER != gameState)  // if game is over, we can't move any longer
        {
            int index = camera.Update(altitude, entities);
            ChasedByMonsters(camera, entities, theTerrain);
            if (-1 != index)  // collision detected
            {
                Entity& collidedEntity = entities[index];
                if (collidedEntity.GetIsPickable())
                {
                    GLfloat x = rand() % ((int)ENTITY_POS_MAX_X * 2) - ENTITY_POS_MAX_X;
                    GLfloat z = rand() % ((int)ENTITY_POS_MAX_Z * 2) - ENTITY_POS_MAX_Z;
                    GLfloat y = theTerrain.GetAltitudeAt(x, z);
                    collidedEntity.SetPosition(glm::vec3(x, y, z));
                }
                PickUpSomething(collidedEntity.GetType());
            }
            // freeze time
            if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE))
            {
                currentTimeSpacePressed = glfwGetTime();
                if (currentTimeSpacePressed - previousTimeSpacePressed > 0.5)
                {
                    isTimeFrozen = !isTimeFrozen;
                    cerr << "Is time frozen? " << isTimeFrozen << endl;
                    MyCLock.PauseTime(isTimeFrozen);
                    previousTimeSpacePressed = currentTimeSpacePressed;
                }
            }
        }

        else if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R))  // replay
        {
            break;
        }

        if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_G) && GAME_NEAR_WIN == gameState)  // G for go back home
        {
            gameState = GAME_WIN;
            // remove the old house
            entities.erase(entities.begin());
            // new house
            RawModel *mHouse = ObjLoader::LoadModel("house", loader);
            ModelTexture mtHouse(loader.LoadTexture("house"));
            TexturedModel tmHouse(mHouse, mtHouse);
            GLfloat x, z, y;
            glm::vec3 standardScale = glm::vec3(1, 1, 1);
            glm::vec3 noRotation = glm::vec3(0, 0, 0);
            x = 0.0f;
            z = 0.0f;
            y = theTerrain.GetAltitudeAt(x, z);
            entities.push_back(Entity(tmHouse, glm::vec3(x, y, z), noRotation, standardScale * 0.5f));
        }

        // exit here
        if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))
        {
#if DEBUG
            cerr << "Captured an escape\n";
#endif
            glfwTerminate();
            exit(0);
        }

        // terrain
        for (Terrain& tmpTerrain: terrains)
        {
            renderer.AddTerrain(tmpTerrain);
        }


        // entities
        for (Entity& tmpEntity: entities)
        {
            renderer.AddEntity(tmpEntity);
        }
        renderer.Render(light, camera);

        //sky
        skyRenderer.Render(PreciseTime);

        // if 1 hour passes, we have to consume energy
        currentDay = MyCLock.GetDay();
        currentHour = MyCLock.GetHour();
        PreciseTime = MyCLock.GetTimeofDay();

        if (previousHour != currentHour)
        {
            ConsumeEnergy();
            previousHour = currentHour;
        }
        // if we are back home, then we can +1s
        if (cameraX * cameraX + cameraZ * cameraZ <= LIFE_TREE_COVER_RADIUS * LIFE_TREE_COVER_RADIUS)
        {
            ReplenishEnergy();
        }

        textRenderer.Render(StatusBar(currentDay, currentHour));

        display->Update();
        display->ShowFPS();
        light.UpdateLight(PreciseTime,camera.GetPosition());
    }
    // clean
    for (RawModel *model: rawModels)
    {
        delete model;
    }
    for (Terrain &t: terrains)
    {
        delete t.GetModel();
    }
}

void Game::BuildWorld(Loader& loader, vector<Entity>& entities, Terrain& theTerrain, vector<RawModel *>& rawModels)
{
    int i;
    GLfloat x, z, y, rotateAngle;
    glm::vec3 standardScale = glm::vec3(1, 1, 1);
    glm::vec3 noRotation = glm::vec3(0, 0, 0);

    // stall, our old house
    RawModel *mStall = ObjLoader::LoadModel("stall", loader);
    rawModels.push_back(mStall);
    ModelTexture mtStall(loader.LoadTexture("stall"));
    TexturedModel tmStall(mStall, mtStall);
    x = 0.0f;
    z = 0.0f;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmStall, glm::vec3(x, y, z), noRotation, standardScale * 1.5f));

    // low poly tree
    RawModel *mTree = ObjLoader::LoadModel("lowPolyTree", loader);
    rawModels.push_back(mTree);
    ModelTexture mtTree(loader.LoadTexture("lowPolyTree"));
    TexturedModel tmTree(mTree, mtTree);
    for (i = 0; i < 25; i++)
    {
        x = rand() % ((int)ENTITY_POS_MAX_X * 2) - ENTITY_POS_MAX_X;
        z = rand() % ((int)ENTITY_POS_MAX_Z * 2) - ENTITY_POS_MAX_Z;
        y = theTerrain.GetAltitudeAt(x, z);
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmTree, glm::vec3(x, y, z), glm::vec3(0, rotateAngle, 0), standardScale));
    }

    // box
    RawModel *mBox = ObjLoader::LoadModel("box", loader);
    rawModels.push_back(mBox);
    ModelTexture mtBox(loader.LoadTexture("box"));
    TexturedModel tmBox(mBox, mtBox);
    for (i = 0; i < 20; i++)
    {
        x = rand() % ((int)ENTITY_POS_MAX_X * 2) - ENTITY_POS_MAX_X;
        z = rand() % ((int)ENTITY_POS_MAX_Z * 2) - ENTITY_POS_MAX_Z;
        y = theTerrain.GetAltitudeAt(x, z);
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmBox, glm::vec3(x, y, z), glm::vec3(0, rotateAngle, 0), standardScale, true, Wood));
    }

/*
    // deer
    RawModel *mDeer = ObjLoader::LoadModel("deer", loader);
    rawModels.push_back(mDeer);
    ModelTexture mtDeer(loader.LoadTexture("deer"));
    TexturedModel tmDeer(mDeer, mtDeer);
    x = rand() % ((int)ENTITY_POS_MAX_X * 2) - ENTITY_POS_MAX_X;
    z = rand() % ((int)ENTITY_POS_MAX_Z * 2) - ENTITY_POS_MAX_Z;
    y = theTerrain.GetAltitudeAt(x, z) + 1.5;
    entities.push_back(Entity(tmDeer, glm::vec3(x, y, z), noRotation, standardScale * 0.3f));
*/

    // boar
    RawModel *mBoar = ObjLoader::LoadModel("boar", loader);
    rawModels.push_back(mBoar);
    ModelTexture mtBoar(loader.LoadTexture("boar"));
    TexturedModel tmBoar(mBoar, mtBoar);
    x = rand() % ((int)ENTITY_POS_MAX_X * 2) - ENTITY_POS_MAX_X;
    z = rand() % ((int)ENTITY_POS_MAX_Z * 2) - ENTITY_POS_MAX_Z;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmBoar, glm::vec3(x, y, z), noRotation, standardScale * 0.5f, false));
    //entities.push_back(Entity(tmBoar, glm::vec3(x, y, z), noRotation, standardScale * 0.5f, false, Monster));

    // wolf
    RawModel *mWolf = ObjLoader::LoadModel("wolf", loader);
    rawModels.push_back(mWolf);
    ModelTexture mtWolf(loader.LoadTexture("wolf"));
    TexturedModel tmWolf(mWolf, mtWolf);
    x = rand() % ((int)ENTITY_POS_MAX_X * 2) - ENTITY_POS_MAX_X;
    z = rand() % ((int)ENTITY_POS_MAX_Z * 2) - ENTITY_POS_MAX_Z;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmWolf, glm::vec3(x, y, z), noRotation, standardScale * 0.5f, false));
    //entities.push_back(Entity(tmWolf, glm::vec3(x, y, z), noRotation, standardScale * 0.5f, false, Monster));

    // bear
    RawModel *mBear = ObjLoader::LoadModel("bear", loader);
    rawModels.push_back(mBear);
    ModelTexture mtBear(loader.LoadTexture("bear"));
    TexturedModel tmBear(mBear, mtBear);
    x = rand() % ((int)ENTITY_POS_MAX_X * 2) - ENTITY_POS_MAX_X;
    z = rand() % ((int)ENTITY_POS_MAX_Z * 2) - ENTITY_POS_MAX_Z;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmBear, glm::vec3(x, y, z), noRotation, standardScale * 0.5f, false, Monster));

    //mush
    RawModel *mMush = ObjLoader::LoadModel("Mush", loader);
    ModelTexture mtMush(loader.LoadTexture("Mush"));
    TexturedModel tmMush(mMush, mtMush);
    for (i = 0; i < 20; i++)
    {
        x = rand() % ((int)ENTITY_POS_MAX_X * 2) - ENTITY_POS_MAX_X;
        z = rand() % ((int)ENTITY_POS_MAX_Z * 2) - ENTITY_POS_MAX_Z;
        y = theTerrain.GetAltitudeAt(x, z) + 1.5;
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmMush, glm::vec3(x, y, z), noRotation, standardScale * 3.0f, true, Food));
    }

    //Rock
    RawModel *mRock = ObjLoader::LoadModel("rock", loader);
    rawModels.push_back(mRock);
    ModelTexture mtRock(loader.LoadTexture("rock"));
    TexturedModel tmRock(mRock, mtRock);
    for (i = 0; i < 20; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        y = theTerrain.GetAltitudeAt(x, z);
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmRock, glm::vec3(x, y, z), glm::vec3(0, rotateAngle, 0), standardScale*0.5f, true, Stone));
    }

    //plank
    RawModel *mPlank = ObjLoader::LoadModel("plank", loader);
    rawModels.push_back(mPlank);
    ModelTexture mtPlank(loader.LoadTexture("plank"));
    TexturedModel tmPlank(mPlank, mtPlank);
    for (i = 0; i < 20; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        y = theTerrain.GetAltitudeAt(x, z)+1.5;
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmPlank, glm::vec3(x, y, z), glm::vec3(0, rotateAngle, 0), standardScale, true, Wood));
    }

    RawModel *mApple = ObjLoader::LoadModel("apple", loader);
    rawModels.push_back(mApple);
    ModelTexture mtApple(loader.LoadTexture("apple"));
    TexturedModel tmApple(mApple, mtApple);
    for (i = 0; i < 20; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        y = theTerrain.GetAltitudeAt(x, z)+0.2;
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmApple, glm::vec3(x, y, z), glm::vec3(0, rotateAngle, 0), standardScale, true, Food));
    }

}

string Game::StatusBar(int day, int hour)
{
    string retStr("");
    int hour12Based;
    string amOrpm;
    if (hour != 12 && hour / 12)
    {
        hour12Based = hour % 12;
        amOrpm = "pm";
    }
    else
    {
        hour12Based = hour;
        amOrpm = "am";
    }

    if (GAME_OVER == gameState)  // game over
    {
        retStr = "Game over, press R to replay.";
    }
    else if (GAME_WIN == gameState)
    {
        retStr = "You win! Go back home and enjoy Spring Festival!";
    }

    else  // game is still runnuing, we need to print life, day and time
    {
        retStr += "Life:[";
        int i;
        for (i = 1; i <= life; i++)
        {
            retStr += "#";
        }
        for (; i <= 10; i++) // fill the life bar with space
        {
            retStr += " ";
        }
        retStr += "], Wood: ";
        retStr += to_string(wood);
        retStr += ", Stone: ";
        retStr += to_string(stone);
        retStr += ", Day ";
        retStr += to_string(day);
        retStr += ", ";
        retStr += to_string(hour12Based);
        retStr += amOrpm;
    }
    int len = retStr.length();
    for (int i = len; i < STATUS_STRING_LENGTH; i++)
    {
        retStr += " ";
    }

    return retStr;
}

void Game::ReplenishEnergy(double deltaEnergy)
{
    life = life + deltaEnergy > 10 ? 10 : life + deltaEnergy;
}

void Game::ConsumeEnergy(double deltaEnergy)
{
    if (GAME_WIN == gameState)
    {
        return;
    }

    life = life - deltaEnergy < 0 ? 0 : life - deltaEnergy;
    if (life <= 0)
    {
        gameState = GAME_OVER;
    }
}

void Game::PickUpSomething(EntityType type)
{
    switch (type) {
        case Food: ReplenishEnergy(); break;
        case Wood: this->wood++; break;
        case Stone: this->stone++; break;
        case Monster: ConsumeEnergy(10); break;  // go die
        default: break;
    }

    if (this->wood >= 10 && this->stone >= 10)  // @NOTE must satisfy these conditions to win
    {
        gameState = GAME_NEAR_WIN;
    }
}

void Game::ChasedByMonsters(const Camera& camera, vector<Entity>& entities, Terrain& terrain)
{
    static double previousTime = 0;
    double currentTime;
    currentTime = glfwGetTime();
    for (Entity& entity : entities)
    {
        if (Monster != entity.GetType())  // not a monster
        {
            continue;
        }
        // comput new position
        glm::vec3 monsterPos = entity.GetPosition();
        glm::vec3 direction = camera.GetPosition() - monsterPos;
        direction.y = 0;  // we don't care the y axis
        if (glm::length(direction) > DANGEROUR_DISTANCE)
        {
            continue;
        }
        direction = glm::normalize(direction);
        glm::vec3 step = direction * MONSTER_SPEED;
        glm::vec3 newPos = monsterPos + step;
        newPos.y = terrain.GetAltitudeAt(newPos.x, newPos.z);
        entity.SetPosition(newPos);
        // compute new direction
        if (currentTime - previousTime > 0.8)
        {
            previousTime = currentTime;
        }
        else
        {
            return;
        }

        glm::vec3 orignalDir = glm::vec3(0, 0, 1);  // @NOTE the monster model's view direction must be (0, 0, 1), that is, looking at z axis
        glm::vec3 newDir = glm::vec3(direction.x, 0, direction.z);
        glm::vec3 normal = glm::cross(orignalDir, newDir);
        GLfloat theta = (int)(acos(glm::dot(orignalDir, newDir)) / PI * 180);
        GLfloat newAngle;
        if (normal.y < 0)
        {
            newAngle = -theta;
            if (newAngle < -170)
            {
                newAngle = -newAngle;
            }
            entity.SetRotation(glm::vec3(0, newAngle, 0));
        }
        else if (normal.y > 0)
        {
            newAngle = theta;
            entity.SetRotation(glm::vec3(0, newAngle, 0));
        }
#if 0
            cerr << "theta: " << theta << ", normal: " << normal.y << ", new angle: " << entity.GetRotation().y << endl;
#endif
    }
}
