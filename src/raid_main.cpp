/*******************************************************************************************
*
*   raylib [shaders] example - Model shader
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   Example originally created with raylib 1.3, last time updated with raylib 3.7
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include <iostream>
#include "raylib.h"

#define FPS 60
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

float transitionSpeed = 0.1;

void CameraController(Camera& camera) {
    if (IsKeyDown(KEY_LEFT)) {
        camera.position.x -= transitionSpeed;
        camera.target.x -= transitionSpeed;

    }
    else if (IsKeyDown(KEY_RIGHT)) {
        camera.position.x += transitionSpeed;
        camera.target.x += transitionSpeed;

    }
    else if (IsKeyDown(KEY_UP)) {
        camera.position.y += transitionSpeed;
        camera.target.y += transitionSpeed;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        camera.position.y -= transitionSpeed;
        camera.target.y -= transitionSpeed;
    }
    else if (IsKeyDown(KEY_O)) {
        camera.position.z -= transitionSpeed;
        camera.target.z -= transitionSpeed;

    }
    else if (IsKeyDown(KEY_P)) {
        camera.position.z += transitionSpeed;
        camera.target.z += transitionSpeed;

    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT| FLAG_WINDOW_HIGHDPI| FLAG_INTERLACED_HINT |FLAG_WINDOW_RESIZABLE);      // Enable Multi Sampling Anti Aliasing 4x (if available)

    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - model shader");
    
    

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = Vector3{ 0.0f, 0.0f, -4.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model model = LoadModel("resources/models/watermill.obj");                   // Load OBJ model
    Texture2D texture = LoadTexture("resources/models/watermill_diffuse.png");   // Load model texture

    // Load shader for model
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    Shader shader = LoadShader(0, TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));

    model.materials[0].shader = shader;                     // Set shader effect to 3d model
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Bind texture to model

    Vector3 position = { 0.0f, 0.0f, 0.0f };    // Set model position

    SetCameraMode(camera, CAMERA_CUSTOM);         // Set an orbital camera mode

    SetTargetFPS(FPS);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    bool dragEnable = false;
    // Main game loop


    
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        //----------------------------------------------------------------------------------
        float camMoveSpeed = 0.1;
        
        CameraController(camera);
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(model, position, 0.2f, WHITE);   // Draw 3d model with texture

                DrawGrid(10, 1.0f);     // Draw a grid

            EndMode3D();

            DrawText("(c) Watermill 3D model by Alberto Cano", screenWidth - 210, screenHeight - 20, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);       // Unload shader
    UnloadTexture(texture);     // Unload texture
    UnloadModel(model);         // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}