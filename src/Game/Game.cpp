#include "Game.hpp"
#include <string>
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
    gameState = GAME_RUNNING;
    life = 10;
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
    // add entities, encapsulate this part in a function to make Start() shorter
    BuildWorld(loader, entities, theTerrain);

    // light
    glm::vec3 colorWhite(1.0, 1.0, 1.0);
    glm::vec3 colorRed(1.0,0.0,0.0);
    glm::vec3 lightPosition(0.0, LIGHT_HEIGHT, 0.0);
    SimpleLight light(lightPosition, colorWhite);
    //ClockTime
    ClockTime MyCLock;
//    light.SetColor(colorRed);

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
        if (GAME_RUNNING == gameState)  // if game is over, we can't move any longer
        {
            camera.Update(altitude);
            // freeze time
            if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE))
            {
                currentTimeSpacePressed = glfwGetTime();
                if (currentTimeSpacePressed - previousTimeSpacePressed > 0.5)
                {
                    isTimeFrozen = !isTimeFrozen;
#if 0
                    cerr << "previous time: " << previousTimeSpacePressed << " current time: " << currentTimeSpacePressed << "Is time frozen? " << isTimeFrozen << endl;
#endif
                    MyCLock.PauseTime(isTimeFrozen);
                    previousTimeSpacePressed = currentTimeSpacePressed;
                }
            }
        }
        else if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE))  // if R is pressed, we need to replay
        {
            exit(-1);
        }
        else if (GLFW_PRESS == glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R))  // replay
        {
            break;
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

#if 0
        GLfloat xLocation = camera.GetPosition().x;
        GLfloat zLocation = camera.GetPosition().z;
        GLfloat yGroundLocation = theTerrain.GetAltitudeAt(xLocation, zLocation);
        GLfloat yLocation = camera.GetPosition().y;
        cerr << "location: "<< xLocation << ", " << yLocation << "(" << yGroundLocation << ")" << ", " << zLocation << endl;
        //cerr << "view: "<< camera.GetViewDirection().x << ", " << camera.GetViewDirection().y <<", " << camera.GetViewDirection().z << endl;
        //cerr << "Error: " << glGetError() << std::endl; // 返回 0 (无错误)
#endif
        display->Update();
        display->ShowFPS();
        light.UpdateLight(PreciseTime );
    }
}

void Game::BuildWorld(Loader& loader, vector<Entity>& entities, Terrain& theTerrain)
{
        int i, x, z, y, rotateAngle;
    glm::vec3 standardScale = glm::vec3(1, 1, 1);
    glm::vec3 noRotation = glm::vec3(0, 0, 0);

    // low poly tree
    RawModel mTree = ObjLoader::LoadModel("lowPolyTree", loader);
    ModelTexture mtTree(loader.LoadTexture("lowPolyTree"));
    TexturedModel tmTree(mTree, mtTree);
    for (i = 0; i < 25; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        y = theTerrain.GetAltitudeAt(x, z);
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmTree, glm::vec3(x, y, z), glm::vec3(0, rotateAngle, 0), standardScale));
    }

    // stall
    RawModel mStall = ObjLoader::LoadModel("stall", loader);
    ModelTexture mtStall(loader.LoadTexture("stall"));
    TexturedModel tmStall(mStall, mtStall);
    x = 5.0f;
    z = 5.0f;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmStall, glm::vec3(x, y, z), noRotation, standardScale * 1.5f));

    // deer
    RawModel mDeer = ObjLoader::LoadModel("deer", loader);
    ModelTexture mtDeer(loader.LoadTexture("deer"));
    TexturedModel tmDeer(mDeer, mtDeer);
    x = -20.0f;
    z = -20.0f;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmDeer, glm::vec3(x, y, z), noRotation, standardScale * 0.3f));

    // boar
    RawModel mBoar = ObjLoader::LoadModel("boar", loader);
    ModelTexture mtBoar(loader.LoadTexture("boar"));
    TexturedModel tmBoar(mBoar, mtBoar);
    x = -20.0f;
    z = -40.0f;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmBoar, glm::vec3(x, y, z), noRotation, standardScale * 0.5f));

    // wolf
    RawModel mWolf = ObjLoader::LoadModel("wolf", loader);
    ModelTexture mtWolf(loader.LoadTexture("wolf"));
    TexturedModel tmWolf(mWolf, mtWolf);
    x = -20.0f;
    z = -60.0f;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmWolf, glm::vec3(x, y, z), noRotation, standardScale * 0.5f));

    // bear
    RawModel mBear = ObjLoader::LoadModel("bear", loader);
    ModelTexture mtBear(loader.LoadTexture("bear"));
    TexturedModel tmBear(mBear, mtBear);
    x = -20.0f;
    z = -80.0f;
    y = theTerrain.GetAltitudeAt(x, z);
    entities.push_back(Entity(tmBear, glm::vec3(x, y, z), noRotation, standardScale * 0.5f));

    // box
    RawModel mBox = ObjLoader::LoadModel("box", loader);
    ModelTexture mtBox(loader.LoadTexture("box"));
    TexturedModel tmBox(mBox, mtBox);
    for (i = 0; i < 20; i++)
    {
        x = rand() % 500 - 250;
        z = rand() % 500 - 250;
        y = theTerrain.GetAltitudeAt(x, z);
        rotateAngle = rand() % 360;
        entities.push_back(Entity(tmBox, glm::vec3(x, y, z), glm::vec3(0, rotateAngle, 0), standardScale));
    }

    // fern, we have 4 types of textures
    RawModel mFern = ObjLoader::LoadModel("fern", loader);
    vector<TexturedModel> fernTexturedModels;
    ModelTexture mtFern1(loader.LoadTexture("fern1"));
    ModelTexture mtFern2(loader.LoadTexture("fern2"));
    ModelTexture mtFern3(loader.LoadTexture("fern3"));
    ModelTexture mtFern4(loader.LoadTexture("fern4"));
    fernTexturedModels.push_back(TexturedModel(mFern, mtFern1));
    fernTexturedModels.push_back(TexturedModel(mFern, mtFern2));
    fernTexturedModels.push_back(TexturedModel(mFern, mtFern3));
    fernTexturedModels.push_back(TexturedModel(mFern, mtFern4));
    for (i = 0; i < 20; i++)
    {
        x = rand() % 200 - 100;
        z = rand() % 200 - 100;
        y = theTerrain.GetAltitudeAt(x, z);
        int fernType = rand() % 4;
        entities.push_back(Entity(fernTexturedModels[fernType], glm::vec3 (x, y, z), noRotation, standardScale * 0.5f));
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
        retStr += "], Day ";
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
    life = life - deltaEnergy < 0 ? 0 : life - deltaEnergy;
    if (life <= 0)
    {
        gameState = GAME_OVER;
    }
}
