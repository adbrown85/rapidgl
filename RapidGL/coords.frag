#version 140

// Inputs
in vec4 Coord0;

// Outputs
out vec4 FragColor;

/*
 * Colors the fragment as its texture coordinate.
 */
void main() {
    FragColor = Coord0;
}
