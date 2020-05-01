#include "slimey.hpp"
#include "../../main.hpp"
#include "../../player/ray.hpp"
#include "../../misc/texture_functional.hpp"

void c_slimey::initialize_monster(glm::vec3& position)
{
    this->initialize_surface();
    this->position = position;
}

float test_it = 0;
void c_slimey::render()
{
    if (this->alive == true)
    {
        // Choose texture to draw
        glBindTexture(GL_TEXTURE_2D, main_ptr->read_textures[4]);

        // Setup texture settings
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texture.surface->w, this->texture.surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture.surface->pixels);

        // Enable using texture
        glEnable(GL_TEXTURE_2D);

        if (this->back == true)
        {
            test_it -= 0.01f;

            if (test_it <= 0.0f)
            {
                this->back = false;
            }
        }

        if (this->back == false)
        {
            test_it += 0.01f;

            if (test_it > 3.0f)
            {
                this->back = true;
            }
        }

        if (this->back == false)
        {
            this->position.x += 0.001f;
        }
        else
        {
            this->position.z -= 0.001f;
        }

        // Setup color
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(this->position.x, 0.25f, this->position.z);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(this->position.x + 1, 0.25f, this->position.z);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(this->position.x + 1, 0.0f, this->position.z);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(this->position.x, 0.0f, this->position.z);
        glEnd();

        // Disable using textures
        glDisable(GL_TEXTURE_2D);
    }
}

void c_slimey::update_monster()
{
    this->do_fire();
}

void c_slimey::do_fire()
{
    this->fire_iterator++;

    if (this->fire_iterator > 1000)
    {
    //    this->firing_ray.cast_at_player();
    }
}

void c_slimey::initialize_surface()
{
    this->texture = read_texture(this->file_name);
}

void c_slimey::clean()
{

}