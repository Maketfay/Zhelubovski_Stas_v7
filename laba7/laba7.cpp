#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define STRING_LENGHT 30


using namespace std;

class Detail
{
private:
	string name;
    int weight;
	string material;
public:

	Detail() {}

	Detail(string _name, int _weight, string _material) {
		name = _name;
		weight = _weight;
		material = _material;
	}

	void ShowDetail() {
		cout << name << " " << weight << " " << material << endl;
	}

	bool operator ==(const Detail& item)
	{
		return name == item.name;
	}

	friend class BoxWithDetails;
};

class BoxWithDetails
{
private:
	vector<Detail> box;

	void WriteToTextFile(const string path)
	{
		ofstream fl;
		fl.open(path);

		for (auto i : box) {
			fl << i.name << ' ' << i.weight << ' ' << i.material << "\n";
		}

		fl.close();
	}

	void ReadFromTextFile(const string path)
	{
		box.clear();
		ifstream fl;
		fl.open(path);
		while (fl.good())
		{
			string name;
			int weight;
			string material;

			fl >> name >> weight >> material;
			if (name == "") break;

			Detail det(name, weight, material);
			box.push_back(det);
		}

		fl.close();
	}

	void ReversShowForBinaryFile(string path) 
	{
		box.clear();
		ifstream fl(path, ios::binary | ios::ate);
		bool f1 = false;
		bool f2 = false;
		char ch = '1';


		while (fl.good())
		{
			char name[STRING_LENGHT];
			char weight[STRING_LENGHT];
			char material[STRING_LENGHT];
			int size[] = { 0, 0, 0 };

			int size_tmp = 0;
			int i = 0;
			streampos here = fl.tellg();
			here -= 3;
			fl.seekg(here);
			while (!f1) {

				fl.get(ch);
				here = fl.tellg();

				here -= 2;
				fl.seekg(here);


				if (ch == ' ') {
					size[i++] = size_tmp;
					size_tmp = 0;
				}
				if (ch == '\n') {
					size[i++] = size_tmp;
					size_tmp = 0;
					break;
				}

				if (here == -1) {
					size[i++] = size_tmp + 1;
					f1 = true;
				}
				if (here == 1) {
					f2 = true;
					here += 1;
				}
				size_tmp++;
			}
			here += 2;
			if (here == 1) {
				fl.close();
				ifstream fl(path, ios::binary);
				here = fl.tellg();
				fl.read(name, size[2] - 1);
				name[size[2] - 1] = '\0';
				fl.get(ch);
				fl.read(weight, size[1] - 1);
				weight[size[1] - 1] = '\0';
				fl.get(ch);
				fl.read(material, size[0]+1);
				fl.get(ch);
				material[size[0]+1] = '\0';
				int temp = (int)atof(weight);
				Detail det(string(name), temp, string(material));
				box.push_back(det);
				break;
			}
			else {
				fl.seekg(here);
				fl.read(name, size[2] - 1);
				name[size[2] - 1] = '\0';
				fl.get(ch);
				fl.read(weight, size[1] - 1);
				weight[size[1] - 1] = '\0';
				fl.get(ch);
				fl.read(material, size[0]+1);
				fl.get(ch);
				material[size[0]+1] = '\0';
				int temp = (int)atof(weight);
				Detail det(string(name), temp, string(material));
				box.push_back(det);
				here = fl.tellg();
				here -= size[0];
				here -= size[1];
				here -= size[2];
				here -= 1;
				fl.seekg(here);
			}

		}

		fl.close();

		Show();
	}

public:

	BoxWithDetails()
	{
	}

	void WriteToFile(const string path, bool IsBinary) 
	{
		if (IsBinary == 1) {
			ofstream fl(path, ios::binary|ios::out);

			for (auto i : box) {
				fl.write(i.name.c_str(), i.name.size());
				fl.write(" ", 1);
				fl.write(to_string(i.weight).c_str(), to_string(i.weight).size());
				fl.write(" ", 1);
				fl.write(i.material.c_str(), i.material.size());
				fl.write("\n", 1);
			}

			fl.close();
		}
		else WriteToTextFile(path);
	}

	void ReadFromFile(const string path, bool IsBinary) 
	{
		if (IsBinary == 0) {
			ReadFromTextFile(path);
			return;
		}
		box.clear();
		ifstream fl(path, ios::binary);
		bool f1 = false;
		char ch = '1';

		while (fl.good()) 
		{
			char name[STRING_LENGHT];
			char weight[STRING_LENGHT];
			char material[STRING_LENGHT];
			int size[] = { 0, 0, 0 };
			
			int size_tmp = 0;
			int i = 0;
			streampos here = fl.tellg();
			while(!(f1 == true && ch == '1')) {
				f1 = true;
				fl.get(ch);
				if (ch == ' ') {
					size[i++] = size_tmp;
					size_tmp = 0;
				}
				if (ch == '\n') {
					size[i++] = size_tmp;
					size_tmp = 0;
					break;
				}
				size_tmp++;
			}
			
			fl.seekg(here);
			fl.read(name, size[0]);
			name[size[0]] = '\0';
			if (string(name).size() == 0) {
				break;
			}
			fl.get(ch);
			fl.read(weight, size[1]-1);
			weight[size[1]-1] = '\0';
			fl.get(ch);
			fl.read(material, size[2]-1);
			fl.get(ch);
			material[size[2]-1] = '\0';
			int temp = (int)atof(weight);
			Detail det(string(name), temp, string(material));
			box.push_back(det);
		}

		fl.close();
	}

	void AddDetail(Detail& detail) 
	{
		box.push_back(detail);
	}

	void Show() 
	{
		for (auto i : box)
		{
			i.ShowDetail();
		}
	}

	void ReverseShow(string path, bool IsBinary)
	{
		if (IsBinary == 1) {
			ReversShowForBinaryFile(path);
			return;
		}
		box.clear();
		ifstream fl(path, ios::binary|ios::ate);
		bool f1 = false;
		bool f2 = false;
		char ch = '1';

		
		while (fl.good())
		{
			char name[STRING_LENGHT];
			char weight[STRING_LENGHT];
			char material[STRING_LENGHT];
			int size[] = { 0, 0, 0 };

			int size_tmp = 0;
			int i = 0;
			streampos here = fl.tellg();
			here -= 3;
			fl.seekg(here);
			while (!f1) {
		
				fl.get(ch);
				here = fl.tellg();
				
					here -= 2;
					fl.seekg(here);
				
				
				if (ch == ' ') {
					size[i++] = size_tmp;
					size_tmp = 0;
				}
				if (ch == '\n') {
					size[i++] = size_tmp;
					size_tmp = 0;
					break;
				}
				
				if (here == -1) {
					size[i++] = size_tmp+1;
					f1 = true;
				}
				if (here == 1) {
					f2 = true;
					here += 1;
				}
				size_tmp++;
			}
			here += 2; 
			if (here == 1) {
				fl.close();
				ifstream fl(path, ios::binary);
				here = fl.tellg();
				fl.read(name, size[2] - 1);
				name[size[2] - 1] = '\0';
				fl.get(ch);
				fl.read(weight, size[1] - 1);
				weight[size[1] - 1] = '\0';
				fl.get(ch);
				fl.read(material, size[0]);
				fl.get(ch);
				material[size[0]] = '\0';
				int temp = (int)atof(weight);
				Detail det(string(name), temp, string(material));
				box.push_back(det);
				break;
			}
			else {
				fl.seekg(here);
				fl.read(name, size[2] - 1);
				name[size[2] - 1] = '\0';
				fl.get(ch);
				fl.read(weight, size[1] - 1);
				weight[size[1] - 1] = '\0';
				fl.get(ch);
				fl.read(material, size[0]);
				fl.get(ch);
				material[size[0]] = '\0';
				int temp = (int)atof(weight);
				Detail det(string(name), temp, string(material));
				box.push_back(det);
				here = fl.tellg();
				here -= size[0];
				here -= size[1];
				here -= size[2];
				here -= 1;
				fl.seekg(here);
			}
			
		}

		fl.close();

		Show();

	}

	void FindElement(string path, string name) {
		box.clear();

		ifstream fl;
		fl.open(path);
		while (fl.good()) {
			string dinamicName;
			int weight;
			string material;
			fl >> dinamicName >> weight >> material;
			if (name == dinamicName) {
				Detail det(name, weight, material);
				box.push_back(det);
			}
		}
		Show();

		fl.close();
	}

    void DeleteFile(string path, string nasme, bool IsBinary) {
        ReadFromFile(path, IsBinary);

        if (box.size() == 0)
            return;

        for (auto i : box) 
		{
			string tmp = i.name;
			if (tmp == nasme)
                box.erase(find(box.begin(), box.end(), i));
        }
        WriteToFile(path, IsBinary);
    }
};



int main()
{
	try {
		setlocale(LC_ALL, "ru");;
		string path;
		BoxWithDetails boxwithdetails = BoxWithDetails();
		bool binaryFail = 0;
		int bin;
		cout << "1 - Работа с бинарным файлом, 2 - Работа с текстовым файлом" << endl;
		cin >> bin;
		switch (bin)
		{
		case 1:
		{

			path = "detail.bin";
			binaryFail = true;
			break;
		}
		case 2:
		{

			path = "detail.txt";

			cout << "1 - Работа с текстовым файлом в текстовом режиме, 2 - Работа с текстовым файлом в бинарном режиме"<<endl;
			int k;
			cin >> k;

			if (k == 2) binaryFail = true;
			else binaryFail = false;
			break;

		}
		default: { throw exception("Bad input");}
		}

		while (true) {
			cout << "1.Добавить элемент \n2.Удалить элемент \n3.Вывести список из всех элементов(включая измененные) \n4.Найти элемент \n5.Сохранить изменения \n6.Прочитать информацию из файла \n7.Реверсивный вывод \n" << endl;
			int tmp;
			cin >> tmp;
			switch (tmp) {
			case 1: 
			{
				string name;
				int weight;
				string material;

				cout << "Введите название детали" << endl;
				cin >> name;
				cout << "Введите вес детали" << endl;
				cin >> weight;
				cout << "Введите материал" << endl;
				cin >> material;

				Detail d1(name, weight, material);
				boxwithdetails.AddDetail(d1);
				break;
			}

			case 2: 
			{
				cout << "Введите название детали, которую хотите удалить " << endl;
				string name;
				cin >> name;
				boxwithdetails.DeleteFile(path, name, binaryFail);
				break;
			}

			case 3: 
			{
				boxwithdetails.Show();
				break;
			}

			case 4:
			{
				cout << "Введите название детали, которую хотите найти " << endl;
				string name;
				cin >> name;
				boxwithdetails.FindElement(path, name);
				break;
			}

			case 5: 
			{
				boxwithdetails.WriteToFile(path, binaryFail);
				break;
			}

			case 6:
			{
				cout << "Последние изменения могут не сохраниться. Вы уверены(1/2)";
				int p;
				cin >> p;
				if (p == 1) {
					boxwithdetails.ReadFromFile(path, binaryFail);
				}
				break;
			}
			
			case 7: 
			{
				
				if(path == "detail.bin")
					boxwithdetails.ReverseShow(path, binaryFail);
				else boxwithdetails.ReverseShow(path, 0);
				break;
			}

			default: {break;}

			}
		
		}
	}
	catch (...) {
		terminate();
	}
	return 0;
	
}

