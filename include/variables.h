
#ifndef VARIABLES_HEADER
#define VARIABLES_HEADER
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 

EXTERN std::string outputFile;
EXTERN int maxDepth;

// Materials (read from file) 
// With multiple objects, these are colors for each.
EXTERN float ambient[3]; 
EXTERN float diffuse[3] ; 
EXTERN float specular[3] ; 
EXTERN float emission[3] ; 
EXTERN float shininess ; 
EXTERN float refractIndex ; 
EXTERN float attenuation[3]; 


#endif