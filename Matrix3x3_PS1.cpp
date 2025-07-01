#include "Matrix3x3.h"
#include <cassert>


//matrix Eqivilance
bool Matrix3x3::operator==(const Matrix3x3& aOther) const noexcept 
{
    return ((*this).row(0) == aOther.row(0)) &&
           ((*this).row(1) == aOther.row(1)) &&
           ((*this).row(2) == aOther.row(2));
}

//matrix Multiplication
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept {

    const Matrix3x3& M = *this;

    const Vector3D lcol0 = aOther.column(0);
    const Vector3D lcol1 = aOther.column(1);
    const Vector3D lcol2 = aOther.column(2);

    return Matrix3x3(Vector3D(M[0].dot(lcol0), M[0].dot(lcol1), M[0].dot(lcol2)),
                    Vector3D(M[1].dot(lcol0), M[1].dot(lcol1), M[1].dot(lcol2)),
                    Vector3D(M[2].dot(lcol0), M[2].dot(lcol1), M[2].dot(lcol2)));
    
}

//matrix Transpose
Matrix3x3 Matrix3x3::transpose() const noexcept {
    Matrix3x3 result;

    const Vector3D lcol0 = (*this).column(0);
    const Vector3D lcol1 = (*this).column(1);
    const Vector3D lcol2 = (*this).column(2);

    result.fRows[0] = Vector3D(lcol0.x(), lcol0.y(), lcol0.w());
    result.fRows[1] = Vector3D(lcol1.x(), lcol1.y(), lcol1.w());
    result.fRows[2] = Vector3D(lcol2.x(), lcol2.y(), lcol2.w());

    return result;
}


//Determinant of a Matrix 
float Matrix3x3::det() const noexcept
{
    const Matrix3x3& M = *this;

    return M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
        - M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])
        + M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
}


//matrix Invertable test 
bool Matrix3x3::hasInverse() const noexcept
{
    return det() != 0;
}

//matrix inverse 
Matrix3x3 Matrix3x3::inverse() const noexcept 
{
    const Matrix3x3& M = *this;
    float ldeterminant = M.det();
    assert(ldeterminant != 0 && "Matrix is not invertible!");

    Matrix3x3 lCofactorMatrix(
        Vector3D(
            (M[1][1] * M[2][2] - M[1][2] * M[2][1]), 
            -(M[0][2] * M[2][1] - M[0][1] * M[2][2]), 
            (M[0][1] * M[1][2] - M[0][2] * M[1][1])  
        ),
        Vector3D(
            -(M[1][2] * M[2][0] - M[1][0] * M[2][2]), 
            (M[0][0] * M[2][2] - M[0][2] * M[2][0]), 
            -(M[0][2] * M[1][0] - M[0][0] * M[1][2]) 
        ),
        Vector3D(
            (M[1][0] * M[2][1] - M[1][1] * M[2][0]), 
            -(M[0][1] * M[2][0] - M[0][0] * M[2][1]), 
            (M[0][0] * M[1][1] - M[0][1] * M[1][0])   
        )
    );

    float lInvDet = 1.0f / ldeterminant;

    return Matrix3x3
    (
        Vector3D(
            lInvDet * lCofactorMatrix[0][0],
            lInvDet * -lCofactorMatrix[0][1],
            lInvDet * lCofactorMatrix[0][2]
        ),
        Vector3D(
            lInvDet * -lCofactorMatrix[1][0],
            lInvDet * lCofactorMatrix[1][1],
            lInvDet * -lCofactorMatrix[1][2]
        ),
        Vector3D(
            lInvDet * lCofactorMatrix[2][0],
            lInvDet * -lCofactorMatrix[2][1],
            lInvDet * lCofactorMatrix[2][2]
       )

    );
}
   
// Output Operator
std::ostream& operator<<(std::ostream& os, const Matrix3x3& M) 
{
    os << "[" << M[0].toString() << "," << M[1].toString() << "," << M[2].toString() << "]";
    return os;
}