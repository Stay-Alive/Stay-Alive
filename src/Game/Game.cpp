#include "Game.hpp"
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
}

Game::~Game()
{
    delete display;
    glfwTerminate();
}

void Game::Start()
{
    cerr << "Game started\n";
    Loader loader;
    srand(time(NULL));  // initialize random number generation

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
    glm::vec3 lightPosition(0.0, LIGHT_HEIGHT, 0.0);
    SimpleLight light(lightPosition, colorWhite);

    Camera camera;
    Renderer renderer(display->GetAspect());
    TextRenderer textRenderer(loader.LoadTexture("font"));

    while(!display->IsWindowClosed())
    {
        camera.Update(theTerrain.GetAltitudeAt(camera.GetPosition().x, camera.GetPosition().z));
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
        textRenderer.Render("Hello, welcome to our world");
#if DEBUG
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
