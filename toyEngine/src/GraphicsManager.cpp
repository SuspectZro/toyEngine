#include "GraphicsManager.h"
#define SOKOL_IMPL
#define SOKOL_GLCORE33
#include "sokol_gfx.h"
#include "glm/glm.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

namespace {
    struct Uniforms {
        mat4 projection;
        mat4 transform;
    };
}


void GraphicsManager::Startup() {
    glfwInit();
    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const char* p = Default.window_name.c_str();
    window = glfwCreateWindow(Default.window_width, Default.window_height, p, Default.window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
    glfwSetWindowAspectRatio(window, Default.window_width, Default.window_height);
    if (!window)
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    //delete p;
    
    sg_setup(sg_desc{});
    
    // A vertex buffer containing a textured square.
    const struct {
        // position
        float x, y;
        // texcoords
        float u, v;
    } vertices[] = {
        // position       // texcoords
      { -1.0f,  -1.0f,    0.0f,  1.0f },
      {  1.0f,  -1.0f,    1.0f,  1.0f },
      { -1.0f,   1.0f,    0.0f,  0.0f },
      {  1.0f,   1.0f,    1.0f,  0.0f },
    };
    sg_buffer_desc buffer_desc{};
    buffer_desc.data = SG_RANGE(vertices);
    //sg_make_buffer(buffer_desc);
    vertex_buffer = sg_make_buffer(buffer_desc);
    sg_pipeline_desc pipeline_desc{};
    pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;
    pipeline_desc.colors[0].blend.enabled = true;
    pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
    pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;
    
    pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
    pipeline_desc.depth.write_enabled = true;

    pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
    pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

    sg_shader_desc shader_desc{};

    shader_desc.vs.source = R"(
    #version 330
    uniform mat4 projection;
    uniform mat4 transform;
    layout(location=0) in vec2 position;
    layout(location=1) in vec2 texcoords0;
    out vec2 texcoords;
    void main() {
        gl_Position = vec4( position, 0.0, 1.0 );
        texcoords = texcoords0;
    })";

    pipeline_desc.layout.attrs[0];
    pipeline_desc.layout.attrs[1];

    shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
    // The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
    shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
    shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
    shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
    shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

    shader_desc.fs.source = R"(
    #version 330
    uniform sampler2D tex;
    in vec2 texcoords;
    out vec4 frag_color;
    void main() {
        frag_color = vec4(1.0,0.0,0.0,1.0); //texture( tex, texcoords );
        // If we're not drawing back to front, discard very transparent pixels so we
        // don't write to the depth buffer and prevent farther sprites from drawing.
        if( frag_color.a < 0.1 ) discard;
    }
)";
    shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
    shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

    shader_desc.fs.uniform_blocks[0] = shader_desc.vs.uniform_blocks[0];
    pipeline_desc.shader = sg_make_shader(shader_desc);
    pipe = sg_make_pipeline(pipeline_desc);

    
    pa.colors[0].action = SG_ACTION_CLEAR;
    pa.colors[0].value = { /* red, green, blue, alpha floating point values for a color to fill the frame buffer with */
        0.0,1.0,0.0,1.0
    
    
    };
    sg_bindings bindings{};
    bindings.vertex_buffers[0] = vertex_buffer;

    string path = "C:\\Users\\ruiz_\\toyEngine\\toyEngine\\assets\\rbow.png";
    std::cout << path;
    string complete = "rbow";
    loadImage(complete, path);
    std::cout << "loading done \n";


    //binds.fs_images[0] = images[complete];
    binds = bindings;


}

bool GraphicsManager::loadImage(const string& name, const string& path){
    std::cout << "loading \n";
    //std::cout << path << " \n";
    bool arval = false;
    try {
        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

        sg_image_desc image_desc{};
        image_desc.width = width;
        image_desc.height = height;
        image_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
        image_desc.min_filter = SG_FILTER_LINEAR;
        image_desc.mag_filter = SG_FILTER_LINEAR;
        image_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
        image_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
        image_desc.data.subimage[0][0].ptr = data;
        image_desc.data.subimage[0][0].size = (size_t)(width * height * 4);

        sg_image image = sg_make_image(image_desc);
        std::cout << width << " \n";
        std::cout << height << " \n";
        //std::cout << *data << " \n";
        stbi_image_free(data);
        //binds.fs_images[0] = image;
        images[name] = image;
        Sprite s;
        s.name = name;
        s.x = 0;
        s.y = 0;
        s.z = 0;
        s.scale = vec3(10.0, 10.0, 10.0);
        sprites.push_back(s);
        arval = true;
       
    }
    catch (...) {
        
        std::cout << "error image not found at path " << path <<"\n";
        
    }
    
    return arval;
    
}



GLFWwindow* GraphicsManager::getWindowPointer() {
    return window;
}

void GraphicsManager::Shutdown() {
    for (auto name : images) {
        sg_destroy_image(name.second);//first is the name second is the id in gpu
    }
    sg_shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
    
}

void GraphicsManager::Draw() {
    Draw(sprites);
    
}

void GraphicsManager::Draw(const std::vector<Sprite>& allSprites) {
    int height;
    int width;
     glfwGetFramebufferSize(window, &(width), &(height));    
     sg_begin_default_pass(pa, width, height);
     sg_apply_pipeline(pipe);
     Uniforms uniforms;
     // Start with an identity matrix.
     uniforms.projection = mat4{ 1 };
     // Scale x and y by 1/100.
     //uniforms.projection[0][0] = uniforms.projection[1][1] = 1. / 100.;
     uniforms.projection[0][0] = uniforms.projection[1][1] = 1.0;
     // Scale the long edge by an additional 1/(long/short) = short/long.
     
     if (width < height) {
         uniforms.projection[1][1] *= width;
         uniforms.projection[1][1] /= height;
     }
     else {
         uniforms.projection[0][0] *= height;
         uniforms.projection[0][0] /= width;
     }//windoww
     
     for (auto sprite : allSprites) {
        // std::cout << "drawing sprite: " << sprite.name << "\n";
         real x, y, z;
         vec3 scaleI;
         x = sprite.x;
         y = sprite.y;
         z = sprite.z;
         scaleI = sprite.scale;
         vec2 position(x, y);
         
         uniforms.transform = translate(mat4{ 1 }, vec3(position, z)) * scale(mat4{ 1 }, vec3(scaleI));
       //spite width 
         if (width < height) {
             uniforms.transform = uniforms.transform * scale(mat4{ 1 }, vec3(real(width) / height, 1.0, 1.0));
             //uniforms.transform = (uniforms.transform * scale) * vec3(real(width) / height, 1.0, 1.0));
         }
         else {
             uniforms.transform = uniforms.transform * scale(mat4{ 1 }, vec3(1.0, real(height) / width, 1.0));
             //uniforms.transform = (uniforms.transform * scale) * vec3(1.0, real(height) / width, 1.0));

         }
         sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms));
         sg_apply_uniforms(SG_SHADERSTAGE_FS, 0, SG_RANGE(uniforms));
            
         binds.fs_images[0] = images[sprite.name];
         sg_apply_bindings(&binds);
       //  std::cout << "after apply \n";
         sg_draw(0, 4, 1);
       //  std::cout << "end of loop \n";
     }
     //std::cout << "after the loop \n";
     //sg_apply_bindings(&binds);
     //sg_draw(0, 4, 1);
     sg_end_pass();
     sg_commit();
     glfwSwapBuffers(window);
     //std::cout << "end of draw \n";

}