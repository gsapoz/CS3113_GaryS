#ifndef ENTITY_H
#define ENTITY_H

namespace Entities
{
	struct Entity { 
		void Draw();
		void SetSize(float height, float width);
    
		float x;
		float y;
		float angle;
    
		int textureID;
    
		float width;
		float height;
		float speed;
    
		float dir_x;
		float dir_y;
	};
}
#endif