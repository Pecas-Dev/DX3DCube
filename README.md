# 3D Cube with Fading Shader using DirectX11 in C++

## Project Description

**Cube with fading shader made with DirectX 11 from scratch in C++.**

This project demonstrates the creation of a 3D cube rendered using DirectX 11. The project is built entirely from scratch, including window creation, the graphical rendering pipeline, and a simple input system to rotate the cube using the WASD or arrow keys.

## Features

- **Window Creation**: Set up from scratch to create a rendering window.
- **Rendering Pipeline**: Implementation of the entire DirectX 11 rendering pipeline.
- **Input System**: Custom input system for rotating the cube using WASD or arrow keys.
- **Shaders**: Custom vertex and pixel shaders to create a fading color effect on the cube.

## Shaders

### Vertex Shader

The vertex shader transforms the 3D coordinates of each vertex into 2D screen coordinates and passes color information to the pixel shader.

```hlsl
struct VS_INPUT
{
    float4 position : POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

    output.position = mul(input.position, m_world);
    output.position = mul(output.position, m_view);
    output.position = mul(output.position, m_proj);

    output.color = input.color;
    output.color1 = input.color1;

    return output;
}
```

### Pixel Shader

The pixel shader interpolates the colors between color and color1 based on a sine wave function to create a fading effect.

```hlsl
struct PS_INPUT
{
    float4 position: SV_POSITION;
    float3 color: COLOR;
    float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(lerp(input.color, input.color1, (float)((sin((float)(m_time / (float)500.0f)) + 1.0f) / 2.0f)),1.0f);
}
```

## Directory Structure

- Graphics: Contains all graphics-related source and include files such as constant buffer, device context, index buffer, pixel shader, swap chain, vertex buffer, vertex shader, and graphics engine.
- Input: Contains input system and input listener scripts.
- Window: Handles window creation.
- App: Manages the execution of the graphics engine and other scripts.
- main.cpp: Entry point of the application.

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/Pecas-Dev/DX3DCube.git
```

2. Build the project using your preferred IDE (preferably Visual Studio).

3. Run the code inside the IDE to see the 3D cube with the fading shader effect.

## Controls

- W / Up Arrow: Rotate the cube up.
- A / Left Arrow: Rotate the cube left.
- S / Down Arrow: Rotate the cube down.
- D / Right Arrow: Rotate the cube right.

## Credits

This project was created by _**Pecas Dev**_.
