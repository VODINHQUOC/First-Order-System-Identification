/*
 * FirstOrderSysID.cpp
 *
 *  Created on: May 1, 2021
 *      Author: dinh quoc
 */

#include "FirstOrderSysID.h"

FirstOrderSysID::FirstOrderSysID() {
	// TODO Auto-generated constructor stub
	for (uint8_t i=0;i<50;i++)
	{
		CalTheta(y_ss[i], u_ss[i]);
	}

}

FirstOrderSysID::~FirstOrderSysID() {
	// TODO Auto-generated destructor stub
}

void FirstOrderSysID::MatrixDot(uint8_t r1,uint8_t c1, float a[2][2],uint8_t r2,uint8_t c2,float b[2][2],float mult[2][2] )
{
	    // Initializing elements of matrix mult to 0.
    for(int i = 0; i < r1; ++i)
    {
    	        for(int j = 0; j < c2; ++j)
        {
            mult[i][j]=0;
        }
    }

    // Multiplying matrix a and b and storing in array mult.
    for(int i = 0; i < r1; ++i)
    {
    	    for(int j = 0; j < c2; ++j)
    	    {
    	    	for(int k = 0; k < c1; ++k)
            	{
                	mult[i][j] += a[i][k] * b[k][j]*1.0;
            	}
    	    }

    }

}

void FirstOrderSysID::Mat2x2(float a[2][2],float b[2][2],float mult[2][2] )
{
	MatrixDot(2,2,a,2,2,b,mult);
}

void FirstOrderSysID::CalTheta(float y,float u)
{
	if (cntq == 1)
	{
		pre_u=u;
		pre_y=y;
		Pre_P[0][0]=1.0;
		Pre_P[1][1]=1.0;
		Pre_theta[0][0]=0.9;
		Pre_theta[1][0]=0.9;
		cntq = 2;
	}
	else if (cntq > 1)
	{
		Phi[0][0]=-pre_y;    // Phi (k)
		Phi[1][0]=pre_u;
		PhiT[0][0]=-pre_y;
		PhiT[0][1]=pre_u;

		Mat2x2(Phi,PhiT,PPT);
		Mat2x2(PPT,Pre_P,PPT_P);
		Mat2x2(Pre_P,PPT_P,P_PPT_P);

		Mat2x2(Pre_P,Phi,P_Ph);
		Mat2x2(PhiT,P_Ph,PhT_P_Ph);
		P[0][0]=(1.0/Lamda)*( Pre_P[0][0]-1.0*P_PPT_P[0][0]/( Lamda+PhT_P_Ph[0][0] ) );
		P[0][1]=(1.0/Lamda)*( Pre_P[0][1]-1.0*P_PPT_P[0][1]/( Lamda+PhT_P_Ph[0][0] ) );
		P[1][0]=(1.0/Lamda)*( Pre_P[1][0]-1.0*P_PPT_P[1][0]/( Lamda+PhT_P_Ph[0][0] ) );
		P[1][1]=(1.0/Lamda)*( Pre_P[1][1]-1.0*P_PPT_P[1][1]/( Lamda+PhT_P_Ph[0][0] ) );

		L[0][0]=1.0*P_Ph[0][0]/( Lamda + PhT_P_Ph[0][0] );
		L[0][1]=1.0*P_Ph[0][1]/( Lamda + PhT_P_Ph[0][0] );
		L[1][0]=1.0*P_Ph[1][0]/( Lamda + PhT_P_Ph[0][0] );
		L[1][1]=1.0*P_Ph[1][1]/( Lamda + PhT_P_Ph[0][0] );

		Mat2x2(PhiT,Pre_theta,PhT_PreTheta);

		epsilon=y-PhT_PreTheta[0][0];

		theta[0][0]=Pre_theta[0][0]+1.0*epsilon*L[0][0];
		theta[0][1]=Pre_theta[0][1]+1.0*epsilon*L[0][1];
		theta[1][0]=Pre_theta[1][0]+1.0*epsilon*L[1][0];
		theta[1][1]=Pre_theta[1][1]+1.0*epsilon*L[1][1];

		Pre_P[0][0]=P[0][0];
		Pre_P[0][1]=P[1][0];
		Pre_P[1][0]=P[0][1];
		Pre_P[1][1]=P[1][1];

		Pre_theta[0][0]=theta[0][0];
		Pre_theta[1][0]=theta[1][0];
		Pre_theta[0][1]=theta[0][1];
		Pre_theta[1][1]=theta[1][1];

		pre_u=u;
		pre_y=y;

	}

}
float FirstOrderSysID::GetPole(void)
{
	return theta[0][0];
}
float FirstOrderSysID::GetZero(void)
{
	return theta[1][0];
}
