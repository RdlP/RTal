#ifndef GOEMETRY_HEADER
#define GOEMETRY_HEADER
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 

class Geometry
{
	public:
		Geometry(mat4 transform): m_transform(transform){
			m_transform_inv = glm::inverse(transform);
		}
		virtual ~Geometry() {}
		virtual Intersection hit(Ray ray) = 0;
		void setMaterial(Material *material)
		{
			m_material = material;
		}
		Material* getMaterial()
		{
			return m_material;
		}
		mat4 getTransform()
		{
			return m_transform;
		}
		mat4 getInverseTransform()
		{
			return m_transform_inv;
		}
	private:
		mat4 m_transform;
		mat4 m_transform_inv;
		Material *m_material;
};
#endif