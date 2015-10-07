attribute vec3 v_position;
attribute vec2 v_color;
attribute vec3 v_normal;

varying vec2 color;
uniform mat4 mvpMatrix;

void main(void)
{
   gl_Position = mvpMatrix * vec4(v_position, 1.0);
   color = v_color;
}

