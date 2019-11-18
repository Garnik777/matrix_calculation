#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <iomanip>


struct Matrix{
private:	
	unsigned int m_row;
	unsigned int m_column;
	int* m_data;
public:	
	Matrix(unsigned int M, unsigned int N): m_row(M), m_column(N) {
		m_data = new int [M * N];
	}
	
	unsigned int getMatrixRow() const {
		return m_row;
	}

	unsigned int getMatrixCol() const {
		return m_column;
	}

	const int& operator ()(int i, int j) const {
		return m_data[i * getMatrixCol() + j];
	}

	int& operator() (int i, int j) {
		return m_data[i * getMatrixCol() +j];
	}
	
	
	~Matrix() {
		delete[] m_data;
	}	
};

struct Readfile{
private:	
	const char* filename;
	unsigned int row;
        unsigned int col;
public:
	std::ifstream file_stream;	
	Readfile(const char* fn): filename(fn) {
		file_stream.open(filename, std::ios::in);
		assert(file_stream.is_open() && "file is not opening\n");
		char delimiter;
		std::string text;
		if(!(file_stream >> row >> delimiter >> col >> text)) {
			std::cout << "can not read first row value\n";
		}	
	}

	bool read(int& i) {
 		if(file_stream >> i) {
			return true;
		}else{
			return false;
		}	
	}
		
	bool read(char& c) {
		if(file_stream >> c) {
			return true;
		}else{
			return false;
		}
	}

	unsigned int read_row_size() {
		return row;
	}

	unsigned int read_col_size() {
		return col;
	}	
	
	~Readfile() {
		file_stream.close();	
	}
};	

struct Writefile{
private:	
	const char* filename;
	unsigned int row;
        unsigned int col;
	int stream_width;
public:
	std::ofstream fout_stream;	
	Writefile(const char* fn, int sw,unsigned int r,unsigned int c)
	       	: filename(fn), stream_width(sw), row(r), col(c){
		fout_stream.open(filename, std::ios::out);
		assert(fout_stream.is_open() && "file_stream is not open\n");
		if(!(fout_stream << row << " x " << col << "\n")) {
			std::cout << " can not write first row value\n";
		}
	}

	bool write(int& i) {
		if(fout_stream << std::setw(stream_width)<< i) {
			return true;
		}else{
			return false;
		}	
	}

	bool char_writer(char c) {
		if(fout_stream << c) {
			return true;
		}else{
			return false;
		}	
	}

	unsigned int write_row_size() {
		return row;
	}

	unsigned int write_col_size() {
		return col;
	}

	~Writefile() {
		fout_stream.close();
	}	
};

void readMatrix(Readfile& r, Matrix& m) {
	char c;
	int x = 0;
	r.read(c);
	r.read(x);
	r.read(c);
	for(int i = 0;i<m.getMatrixRow();i++)
	{
		for(int j = 0;j< m.getMatrixCol();j++)
		{
			m(i, j) = x;
			if(r.read(x))
			{
				std::cout<< m(i,j) <<" ";
			}	
			else{
				std::cout<<"can not read"<<std::endl;
			}
		}
		
			std::cout<< std::endl;
	} 
			std::cout<<"read matrix done"<<std::endl;
}

void AddMatrix(const Matrix& M, const Matrix& N,Matrix& C)
{
	assert(M.getMatrixRow() == N.getMatrixRow());
	assert(M.getMatrixCol() == N.getMatrixCol());
	for(int i = 0;i<M.getMatrixRow();i++)
	{
		  for(int j=0;j<N.getMatrixCol();j++)
		  {
			C(i,j)=M(i,j) + N(i,j);
		  }
	}
	std::cout << "add matrix done" <<std::endl;
}

void MultMatrix(const Matrix& M, const Matrix& N, Matrix& K)
{
	assert(M.getMatrixCol() == N.getMatrixRow());
	assert(M.getMatrixRow() == K.getMatrixRow());
	assert(N.getMatrixCol() == K.getMatrixCol());
//	int transpos = (M.getMatrixRow() >= 100 && N.getMatrixCol() >= 100) ?  1 : 0;
	for(int i = 0;i < M.getMatrixRow();i++)
	{
		for(int j = 0; j< N.getMatrixCol();j++)
		{
		 int sum = 0;
			for(int k = 0; k < M.getMatrixCol();k++)
			{	
					sum+=M(i,k) * N(k,j);
			}
				K(i,j) = sum;
				std::cout << K(i,j) <<' ';
		}	
	}
		std::cout <<"mult matrix done"<<std::endl;
}

void WriteMatrix(const Matrix& y,Writefile& wy)
{

	int x = 0;
	for(int i = 0;i < y.getMatrixRow();i++)
	{
		for(int j = 0;j < y.getMatrixCol(); j++)
		{
			x=y(i,j);
			if(wy.write(x))
			{
				wy.fout_stream << ' ';
			}else{
				std::cout <<"can not write file"<<std::endl;
			 }
		}
			wy.fout_stream << '\n';
	}
		std::cout<<"write matrix done"<<std::endl;
}

int main()
{	
	unsigned int M = 0;
	unsigned int N = 0;
	unsigned int K = 0;
	int stream_width = 7;
	Readfile ra("a.txt"),rb("b.txt"),rc("c.txt"),rd("d.txt");
	Writefile wy("y.txt", stream_width, ra.read_row_size(), rd.read_col_size());
	Matrix A(ra.read_row_size(), ra.read_col_size()),
	       B(rb.read_row_size(), ra.read_col_size()),
	       T1(ra.read_row_size(),ra.read_col_size()),
	       C(rc.read_row_size(), rc.read_col_size()),
	       D(rd.read_row_size(), rd.read_col_size()),
	       T2(rc.read_row_size(),rc.read_col_size()),
	       Y(ra.read_row_size(), rd.read_col_size());
	readMatrix(ra, A);
	readMatrix(rb, B);
	AddMatrix(A,B,T1);
	readMatrix(rc, C);
	readMatrix(rd, D);
	AddMatrix(C,D,T2);
	MultMatrix(T1,T2,Y);
	WriteMatrix(Y,wy); 
    
return 0;
}


