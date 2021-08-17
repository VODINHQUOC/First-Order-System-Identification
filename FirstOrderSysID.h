/*
 * FirstOrderSysID.h
 *
 *  Created on: May 1, 2021
 *      Author: dinh quoc
 */

#ifndef SRC_FIRSTORDERSYSID_H_
#define SRC_FIRSTORDERSYSID_H_
#include <stdint.h>
class FirstOrderSysID {
public:
	FirstOrderSysID();
	virtual ~FirstOrderSysID();
	void MatrixDot(uint8_t r1,uint8_t c1, float a[2][2],uint8_t r2,uint8_t c2,float b[2][2],float mult[2][2] );
	void Mat2x2(float a[2][2],float b[2][2],float mult[2][2] );
	void CalTheta(float y,float u);
	float GetZero(void);
	float GetPole(void);

private:
	float Phi[2][2]= {{0,0},{0,0}};
	float PhiT[2][2]={{0,0},{0,0}};
	float Result[2][2]={{0,0},{0,0}};
	float P[2][2]={{0,0},{0,0}};
	float L[2][2]={{0,0},{0,0}};
	float Pre_P[2][2]={{0,0},{0,0}};
	float Pre_theta[2][2]={{0,0},{0,0}};
	float theta[2][2]={{0,0},{0,0}};
	float pre_u=0;
	float pre_y=0;
    float PPT[2][2]={{0,0},{0,0}};
	float PPT_P[2][2]={{0,0},{0,0}};
	float P_PPT_P[2][2]={{0,0},{0,0}};
	float P_Ph[2][2]={{0,0},{0,0}};
	float PhT_P_Ph[2][2]={{0,0},{0,0}};
	float Lamda =0.995;
	float PhT_PreTheta[2][2]={{0,0},{0,0}};
	float epsilon=0;
	uint8_t cntq=1;
	float u_ss[50]={540,580,620,660,700,740,780,820,860,900,940,
	 980,1020,1060,1100,1140,1180,1220,1260,1300,
	 1340,1380,1420,1460,1500,1540,1580,1620,1660,
	 1700,1740,1780,1820,1860,1900,1940,1980,2020,
	 2060,2100,2140,2180,2220,2260,2300,2340,2380,
	 2420,2460,2500};
	float y_ss[50]={31,35,41,45,50,55,60,65,69,74,79,84
	    ,89,94,98,102,108,112,117,122,127,
	    132,133,142,146,151,155,160,165,167,
	    174,179,184,189,193,199,203,208,213,
	    216,222,226,231,236,239,245,249,252,
	    253,253};
};


#endif /* SRC_FIRSTORDERSYSID_H_ */
