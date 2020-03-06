#include <iostream>
#include <pthread.h>

using namespace std;

struct data{
	
	int X0;
	int a;
	int c;
	int m;
	int N;
};


class lab1
{
public:
	lab1(data par) : param(par) 
	{
	
	}
	~lab1() 
	{
	}
	
private:

	static void* start_thread(void *temp)
	{
		lab1* cur = (lab1*) temp;
		return cur->calculation(cur);
	}

	void* calculation(lab1* cur)
        {
		data curPar = cur->getParam();
                int *rez = new int (curPar.N);
                rez[0] = curPar.X0;
                for (int i = 1; i < curPar.N; i++)
                {
                        rez[i] = (curPar.a*curPar.X0 + curPar.c) % curPar.m;
                	curPar.X0 = rez[i];
		}

                return rez;
        };
	
public:
	void start_thread()
	{
		void *per;
		int *sum;
		pthread_create(&tid, NULL, start_thread, this);
		pthread_join(tid, &per);
		sum = (int*)per;

		for (int i = 0; i < param.N; i++)
			cout << sum[i] << " ";
		cout << endl;

		delete sum;
	};

	data getParam()
	{
		return param;
	}



private:
	pthread_t tid;
	data param;

};


int main()
{
	cout << "enter X0, a, c, m, N" << endl;

	data dt;
	cin >> dt.X0 >> dt.a >> dt.c >> dt.m >> dt.N;

	lab1 lab(dt);
	lab.start_thread();
	return 0;
}
