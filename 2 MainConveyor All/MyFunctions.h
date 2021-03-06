#include "stdafx.h"

using namespace std;

///


///
const int N=6;
const int MatrixSize = 64; //2^6
const int SpinInPlaquet = 6;
//start test const
const int function_flag=4;
//end test const

const string delim="\\";
const string inp_fin="final_data";
const string inp_matr = "matrixes" + delim;// +"b2_";
const string inp_route="input_routes"+delim;
const string out_res="results_";

const string type1="l";
const string type2="nl";
const string type3="ns";

const int maxIntElem=5; //
const int Namount=256;   //���������� ��������� ground-��������� 8
const int resAmount=45; //���-�� ��������� J �������� � 8 �������
const int matrixResAmount=429; //���-�� ��������� ��������� � ���� ������ ���������� � 8 �������



struct step
{
	step(int x,int y)
	{
		sx=x;
		sy=y;
	}
	int sx;
	int sy;
	bool operator==(step s2)
	{
		if((sx==s2.sx)&&(sy==s2.sy))
		{
			return true;
		}
		else
			return false;
	}
};

struct state
{
	double factor; //�������� ���������

	//!!! ��������� char �� ��
	char coeff[3];  //������� ������������� J1,J2 � (J2-J1)
	char states[N];// ������ ��������� �� ��������������� ��������
	bool operator<(const state &s) const//������ ��� 2�� ���������, ���������� � ������ ��������
	{
		int i=0;
		while(i<N)
		{
			if(states[i]<s.states[i]) return true;
			else if(states[i]>s.states[i]) return false;
			i++;
		}
		i=0;
		while(i<3)
		{
			if(coeff[i]<s.coeff[i]) return true;
			else if(coeff[i]>s.coeff[i]) return false;
			i++;
		}
		return false;
	}


	bool operator==(const state s) const//��������� ����� ���� ������ ���� ��������� �����
	{
		for (int i = 0; i < N; i++)
			if (states[i] != s.states[i])
				return false;
		for (int i = 0; i<3; i++)
			if (s.coeff[i] != coeff[i])
				return  false;
		return true;
	}

	bool isEqual(const state s)
	{
		for (int i = 0; i < N; i++)
			if (states[i] != s.states[i])
				return false;
		return true;
	}
};

struct inter
{
	char n1,n2; //������ ��������, ��������� � 0
	char v1,v2; //������ ������, ��������� � 0
	char Jtype; // 0-J1, 1-J2, 2-(J2-J1)
};

struct res
{
	double factors[matrixResAmount]; //�������� ��������� ��� ������ ������������
	//28 - ����� ��������� �������� � 6 �������


	//OK
	res& operator+=(const res &tmp)
	{
		for(int i=0;i<matrixResAmount;i++)
		{
			factors[i]+=tmp.factors[i];
		}
		return *this;
	}

	void minus()
	{
		for(int i=0;i<matrixResAmount;i++)
			factors[i]*=-1;
	}
};


struct edge //��� �������� ��������� �����
{
	int x1,y1,x2,y2;
	bool operator==(edge e2)
	{
		if(((x1==e2.x1)&&(x2==e2.x2)&&(y1==e2.y1)&&(y2==e2.y2))||((x1==e2.x2)&&(x2==e2.x1)&&(y1==e2.y2)&&(y2==e2.y1)))
		{
			return true;
		}
		else
			return false;
	}
	void set(int X1,int Y1,int X2,int Y2)
	{
		x1=X1;
		y1=Y1;
		x2=X2;
		y2=Y2;
	}

};

namespace std{
	template <>
	struct hash<state>
	{
		std::size_t operator()(const state& k) const;
	};
};


//////////////////////////////////////////////////////////////////////////
extern double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize];//����� ������� � �������, ��� ������� SP,SM ��� SZ,����� ����, ����� �������
extern double VmatrixInside[MatrixSize][MatrixSize];//���������� ��� ���������� �����������
extern double Energie[MatrixSize]; //������� ���������
extern inter curInter [N][maxIntElem]; //������ ���������� �������������
extern int interAmount[N];// ���-�� ��-��� � ������ ���������

extern vector<state> vIn[Namount],vOut1[Namount],vOut2[Namount]; //������� ��������-���������� �� ������� ���� ��� ������� ������ ��� ��������, �� ��������� ���� - ��������
extern vector<state> vOutTemp1,vOutTemp2;//������������� �������
extern vector<state> vtemp;
extern vector<state> temp,temp2,tempvec,tempvec2;
extern unordered_map<state, double> map_temp, map_temp2, map_tempvec, map_tempvec2;
extern state init;
//////////////////////////////////////////////////////////////////////////


void returnV(inter curInter[][maxIntElem],int interAmount[],int interN,int n1,int n2,int dx,int dy);//������������� �������� �������������� ����� �����


void generate_all_Jfactors(int n,int **Jfactors);

void generate_all_Jstrings(int n,int **Jfactors,string *strarr);


void collect(vector<state> &outvec,vector<state> &invec);

void act(vector<state> &inv, vector<state> &outv, double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize], int interNumber);

void act_ground(vector<state> &inv, vector<state> &outv, double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize], int interNumber);

void act_energy(vector<state> &inv, vector<state> &outv, double Vmatrix[SpinInPlaquet][3][MatrixSize][MatrixSize], int interNumber);

void act_energy_power(vector<state> &inv, vector<state> &outv, int power, double Vmatrix[4][3][MatrixSize][MatrixSize], int interNumber);

void act_inside(vector<state> &inv,vector<state> &outv,int plaquetNumber );

void act_inside_ground(vector<state> &inv,vector<state> &outv,int plaquetNumber);

void act_inside_enrgy_power(vector<state> &inv,vector<state> &outv,int power,int plaquetNumber );

void generate_procedure_order(int *termorder,int* operatororder,int edge_amount,int num,int *Res,int *power);
