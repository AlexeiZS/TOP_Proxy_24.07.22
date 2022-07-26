
//    Proxy
// + Исключения!!!

//              Задание:
//  Используя паттерн заместитель реализовать proxy.
// 
//      Дано:
// текстовый документ с записями следующего вида.
// 1-я строка - дата последних изменений все последующие
// строки имеют вид: id  данные
// где id - уникальный идентификатор
// 
// для proxy делается запрос на данные по id, proxy определяет
// был ли подобный запрос ранее. Если находит, то сверяет 
// с датой последних изменений в файле.
// Если дата изменений текущего запроса и дата последних
// изменеий не соответствует, то обновляет иинформацию с данного
// id из файла и выдает результат без обновления.
// Если данный запрос не был найден, то добавляет его
// в свой список и выдает результат.


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Cash
{
	string id;
	string data;     //  данные
	string date;     //  дата (последнии изменения).

	bool operator ==(string id)
	{
		return(this->id == id)?true:false;
	}

};

class Proxy
{
private:
	vector <Cash> cash;
	string path;
public:

	Proxy(string path) 
	{
		this->path = path;
	};

	string get(string id) 
	{
		string date;
		string data;
		ifstream in(path);
		if (in.is_open())
		{
			getline(in, date);
		}
		else
		{
			in.close();
			throw " file not found ";
		}
		if (cash.empty())//возвращает true если строка пустая.
		{
			cout << " data from file with add to cash" << endl;
			data = getData(id);
		    cash.push_back(Cash{ id, data, date });
		}
		else 
		{
			bool flag = false;
			for (auto& i : cash)
			{
				if (i.id == id)
				{
					flag = true;
					if (i.date == date)
					{
						cout << " data rfom cash" << endl;
						data = i.data;
					}
					else
					{
						cout << " data from file witch update cash" << endl;
						data = getData(id);
						i.data = data;
						i.date = date;
					}
					break;
				}

			}
		    if(!flag)
			{
			   cout << " data from file add to cash " << endl;
		       data = getData(id);
			   cash.push_back(Cash{ id, data, date });
			}
		}
		in.close();
		return data;
	}

private:
	string getData(string id)
	{
		string data = "";
		string str;
		string buf;
		ifstream in(path);
		if (in.is_open())
		{
			while (getline(in, str))
			{
				buf = " ";
				for (int i = 0; i < str.size(); i++)
				{
					if (str[i] = ' ')break;
					buf += str[i];
				}
				if (id == buf)
				{
					int k = 0;
					for (int i = 0; i < str.size(); i++, k++) {
						if (str[i] == ' ') 
						{
							k++;
							break;
						}
					}
					for (int i = k; i < str.size(); i++)
					{
						data += str[i];
					}
					in.close();
					return data;
				}
			}
		}
		else
		{
			throw "file not found";
		    in.close();
		}
		in.close();
		throw "id not found";
	}
};


void changeDate(string path, string newDate)
{
	string str, str2 = "";
	ifstream in(path);
	while (getline(in, str))
	{
		str2 += str;
		str2 += "\n";
	}
	in.close();
	for (int i = 0; str2[i] != '\n'; i++)
	{
		str2[i] = newDate[i];
	}
	cout << endl << endl << str2 << endl << endl;
	ofstream out(path);
	out << str2;
	out.close();
}

//************************************

float divizion(float a, float b)
{
	if (!b) throw "divizion by zero";
	return a / b;
}

// динамический массив.
template <typename T>
class Array
{
	T* data;
	int size;
	int maxSize;
public:
	Array(int size)
	{
		this->maxSize = size;
		data = new T [maxSize];
	}
	void add(T data)
	{
		if (this->size >= maxSize) 
			throw " array is full! ";
		else
		{
			this->data[size] = data;
			size++;
		}
	}
	void show()
	{
		for (int i = 0; i < size; i++)
		{
			cout << data[i] << " ";
		}
		cout << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "ru");

	//создаем массив размером 3 элемента.
	//Array <int> array(3);
	//try 
	//{
	//	array.add(3);
	//	array.add(5);
	//	array.add(7);
	//	array.add(3);
	//}
	//catch(const char* exception)    // exception (исключение)
	//{
	//	cout << exception;
	//}
	//array.show();



	//try
	//{
	//  cout << divizion(3, 0);
	//}
	//catch (const char* str)
	//{
	//	cout << str;
	//}

	string path = "C:\\Users\\zimov\\Desktop\\Text_Proxy.txt";
	Proxy proxy(path);
	try {
		changeDate(path, "07.12.21");
		cout << proxy.get("1") << endl; //add
		cout << proxy.get("5") << endl; //add
		cout << proxy.get("3") << endl; //from cash
	    cout << proxy.get("37") << endl; //not
		//cout << proxy.get("5") << endl;//update
		//cout << proxy.get("5") << endl;//cash
	}
	catch (const char* exception)
	{
		cout << exception;
	}

	


	/*vector <cash>cash;
	cash cash2{ "23","234","2354" };
	cash cash3{ "237","234","235445645" };
	cash cash4{ "2","23","235564" };
	cash.push_back(cash2);
	cash.push_back(cash3);
	cash.push_back(cash4);

	for (int i = 0; i < cash.size(); i++) {
		cout << cash[i].data << endl;
	}
	for (auto& i : cash)
	{
		cout << i.data;
	}*/

	//cout<<proxy.get("78");








	return 0;
}











