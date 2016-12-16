#version 330

// vertex data
in vec3 p_normal;
//in vec2 p_texcoord;

out vec4 p_color;

// material data
uniform sampler2D m_texture;
uniform vec4 m_ambient;
uniform vec4 m_diffuse;
uniform vec4 m_specular;
uniform vec4 m_emission;
uniform float m_shininess;

// light data
const int LT_POINT = 0;
const int LT_DIRECTIONAL = 1;

uniform int l_type;
uniform vec3 l_position;
uniform vec3 l_direction;

uniform vec4 l_ambient;
uniform vec4 l_diffuse;
uniform vec4 l_specular;

void main() {
    const float l_attenuation = 1.0f;
    
    // compute emission compoennt
    vec4 emission = m_emission;

    // compute ambient component
    vec4 ambient = l_ambient * m_ambient;

    // compute diffuse component
    float factor = max(0.0f, dot(l_direction, p_normal));
    vec4 diffuse = factor * (l_diffuse * m_diffuse);

    // compute specular component
    /*
    vec4 specular = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    if (factor > 0.0f) {
        vec4 specular_blend = l_attenuation * m_specular * l_specular;
        vec3 reflection = reflect(-l_direction, p_normal);
    }
    */
    
    // compute final color
    p_color = emission + ambient + diffuse/* + specular*/;
}
