//Introductory quaternion class
#include <math.h>
#include "vector.h"
#include "mymatrix.h"

namespace MyMathLab
{

class MyQuat
{
	public:
		MyQuat(void);
		MyQuat(float angleDeg, Vector &axis);	//create from axis, angle
		MyQuat(Position &p);	//create from position
		
		~MyQuat(void){;}

		MyQuat addTo(const MyQuat &other) const;
		MyQuat multiplyBy(const MyQuat &other) const;

		float getMagnitude(void) const;	
		void normalise(void);
		MyQuat getConjugate(void) const;	
		MyQuat getInverse(void) const;

		MyMatrix convertToRotationMatrix(void) const; 

		float w;
		Vector v;
};


}