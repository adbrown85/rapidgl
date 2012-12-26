#version 140

// Uniforms
uniform mat4 MVPMatrix = mat4(1.0);

// Inputs
in vec4 MCVertex;

/*
 * Calculates vertex position.
 */
void main() {
    gl_Position = MVPMatrix * MCVertex;
}
