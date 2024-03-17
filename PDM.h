#ifndef PDM_H
#define PDM_H
#include <iostream>
#include <fstream>
#include <conio.h> // _getch(); gotoxy()
#include <windows.h> // WinExec (); SetConsoleCP(1251); SetConsoleOutputCP(1251);
#include <chrono> // std::chrono::seconds
#include <string> // stoi ();
#include <thread>  // std::this_thread::sleep_for
using namespace std;
using std::cout;
using std::sin;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::thread;
class Project {
    int Project_number; // номер проекта, нумерация с '0'
    string Project_name; // название проекта
    string n_Project_name; // название проекта c номером
    void set_Project_number(int number) // установить номер проекта
    {
        Project_number = number;
    }
    void make_n_Project_name() // создает название проекта c номером
    {
        n_Project_name = "\0";
        if (Project_number + 1 < 10) n_Project_name += "0";
        n_Project_name += std::to_string(Project_number + 1) + ". " + Project_name;
    }
public:
    Project() { ; }
    ~Project() { ; }
    int FileExists(string file_name)
    {
        ifstream file(file_name);
        file.close();
        if (file) return 1;
        else return 0;
    }
    bool is_free() // возвращает TRUE, если проект "свободный"
    {
        string f_name = "Prog_workspace\\" + get_n_Project_name() + ".txt";
        if (FileExists(f_name)) return false;
        else return true;
    }
    string get_Project_name() // возвращает название проекта
    {
        return Project_name;
    }
    string get_n_Project_name() // возвращает название проекта с номером
    {
        return n_Project_name;
    }
    void set_Project_name(string name) // установить название проекта // Переписать под дружественную функцию!!!!!!!!!!!
    {
        Project_name = name;
        make_n_Project_name();
    }
    void init_Project(int number, string name) // инициация класса
    {
        set_Project_number(number);
        set_Project_name(name);
    }
    void show() // вывод класса на экран
    {
        if (Project_number + 1 < 10)
        {
            cout << "0" << Project_number + 1 << ". " << Project_name << endl;
        }
        else
        {
            cout << Project_number + 1 << ". " << Project_name << endl;
        }
    }
    void string_to_char(string str, char* ch) // функция перезаписывает из переменной string в массив char. Память под char [] !ДОЛЖНА! быть выделена корректно.
    {
        int str_length = (int)str.length();
        for (int i = 0; i < str_length; i++)
        {
            ch[i] = str[i];
        }
        ch[str_length] = '\0';
    }
    void create_stop_flag() // создает флаг запрета доступа другими пользователями к объекту
    {
        string file_name = "Prog_workspace\\" + get_n_Project_name() + ".txt";
        ofstream file(file_name, std::ios::out);
        file.close();
    }
    void delete_stop_flag() // удаляет флаг запрета доступа другими пользователями к объекту
    {
        string file_name = "Prog_workspace\\" + get_n_Project_name() + ".txt";
        char* f_name = new char[file_name.length() + 1];
        string_to_char(file_name, f_name);
        std::remove(f_name);
        delete[] f_name;
    }
};
class Shell: public Project {
public:
    bool WORK;
    void m()
    {
        cout << "*";
        int i = _getch();
    }
    string Console; // переменная для хранения данных с экрана
    int Console_marker; // точка остановки перед выводом списка проектов
    enum ConsoleColor // перечисление управляет цветом текста
    {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGray = 7,
        DarkGray = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        Yellow = 14,
        White = 15
    };
    void SetTextColorFirst(ConsoleColor text, ConsoleColor background)
    {
        HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
    }
    void string_to_char(string str, char* ch) // функция перезаписывает из переменной string в массив char. Память под char [] !ДОЛЖНА! быть выделена корректно.
    {
        int str_length = (int)str.length();
        for (int i = 0; i < str_length; i++)
        {
            ch[i] = str[i];
        }
        ch[str_length] = '\0';
    }
    string Prog_directory;
    string get_Prog_directory()
    {
        string str = "\0";
        SYSTEMTIME time;
        GetSystemTime(&time);
        string f_name = "prog" + std::to_string(time.wMilliseconds) + ".txt";
        char* file_name = new char[f_name.length() + 1];
        string_to_char(f_name, file_name);
        string com = "echo %cd%\\>\"" + f_name + "\"";
        char* com_cmd = new char[com.length() + 1];
        string_to_char(com, com_cmd);
        system(com_cmd); // system("echo "%cd%">"prog%date%.txt"");
        delete[] com_cmd;
        ifstream file(file_name, std::ios::in);
        char ch;
        while (file)
        {
            ch = file.get();
            if (file && ch != 10) str += ch;
        }
        file.close();
        com = "del \"" + f_name + "\"";
        com_cmd = new char[com.length() + 1];
        string_to_char(com, com_cmd);
        system(com_cmd); //system("del progr%date%.txt");
        delete[] com_cmd;
        delete[] file_name;
        return str;
    }
    int FileExists(string file_name)
    {
        ifstream file(file_name);
        file.close();
        if (file) return 1;
        else return 0;
    }
    string textfile_to_string(string file_name)
    {
        int length = file_name.length();
        char* f_name = new char[length + 1];
        string_to_char(file_name, f_name);
        fstream file(f_name, std::ios::in);
        if (!file) cout << "Ошибка открытия файла" << f_name << endl;
        string text;
        char ch;
        while (file) {
            file.get(ch);
            if (file) text += ch;
        }
        file.close();
        return text;
    }
    string Project_directory;
    int string_to_system_command(string str) // функция переписана под возвращение значения
    {
        int value = 0;
        int length = (int)str.length();
        string str_command = "\0";
        char* cmd_command;
        for (int i = 0; i < length; i++)
        {
            if (str[i] != '\n') str_command += str[i];
            else
            {
                cmd_command = new char[str_command.length() + 1];
                string_to_char(str_command, cmd_command);
                system(cmd_command);
                //cout << cmd_command << endl;
                str_command = "\0";
                delete[] cmd_command;
            }
        }
        if (str_command != "\0")
        {
            cmd_command = new char[str_command.length() + 1];
            string_to_char(str_command, cmd_command);
            value = system(cmd_command);
            str_command = "\0";
            delete[] cmd_command;
        }
        return value;
    }
    string decode_function(string str, int Project_number)
    {
        string word = "\0";
        int word_begin = 0;
        int word_length = 0;
        string s = "\0";
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '%')
            {
                word_begin = i;
                word_length = 1;
                do
                {
                    i++; // нужна проверка что i < str.length(); (ошибка может возникнуть, когда в документе нечетное количество '%')
                    word_length++;
                } while (str[i] != '%');
                word = str.substr(word_begin, word_length);
                word = code_to_str(word, Project_number);
                s += word;
                i++;
            }
            if (i > str.length() - 1) break;
            s += str[i];
        }
        return s;
    }
    string code_to_str(string code, int Project_number)
    {
        string decode = "\0";
        if (Project_number < 0 && code == "%Project_directory%")
        {
            decode = Project_directory.substr(0, Project_directory.length());
            return decode;
        }

        if (code == "%userprofile%") return "\0"; // в тестовой версии данного варианта нет

        if (code == "%N_Project%")
        {
            return prj[Project_number].get_n_Project_name();
        }
        if (code == "%N_00_000_Project%")
        {
            if (Project_number < 10) decode = "0";
            decode += std::to_string(Project_number + 1) + ".00.000 " + prj[Project_number].get_Project_name();;
            return decode;
        }
        if (code == "%Project_directory%")
        {
            decode = Project_directory.substr(0, Project_directory.length() - 1); // без последнего символа '\'
            return decode;
        }
        if (code == "%Prog_workspace%")
        {
            decode = Prog_directory + "Prog_workspace";
            return decode;
        }
        if (code == "%user_Project_directory%")
        {
            decode = user_Project_directory.substr(0, user_Project_directory.length() - 1);// без последнего символа '\'
            return decode;
        }
        return "\0";
    }
    int create_Project_directory()
    {
        string str = textfile_to_string("Prog_files\\Create_New_Folder_IF_Necessary.txt");
        str = decode_function(str, -1);
        string_to_system_command(str);
        return 0;
    }
    string get_Project_list() // возвращает перечень проектов ввиде сплошного текста
    {
        string str = "\0";;
        string com = "dir /b " + Project_directory + ">Project_list.txt";
        char* com_cmd = new char[com.length() + 1];
        string_to_char(com, com_cmd);
        system(com_cmd);
        if (FileExists("Project_list.txt")) str += textfile_to_string("Project_list.txt");
        else solve_the_Error(1);
        system("del Project_list.txt");
        return str;
    }
    int number_of_str_in_string(string str)
    {
        int counter = 0;
        int length = (int)str.length();
        for (int i = 0; i < length; i++)
        {
            if (str[i] == '\n') counter++;
        }
        if (str[length - 1] != '\n') counter++;
        return counter;
    }
    int get_number_of_the_Projects()
    {
        return number_of_str_in_string(get_Project_list());
    }
    class Project* prj; // указатель на динамический список проектов
    int number_of_the_Projects;
    int Active_project_number; // номер выбранного проекта (нумерация с "0")
    string user_Project_directory;
    string get_user_Project_directory() // возвращает директорию хранения проектов юзером на ПК
    {
        string str = "\0";
        SYSTEMTIME time;
        GetSystemTime(&time);
        string f_name = "user" + std::to_string(time.wMilliseconds) + ".txt";
        char* file_name = new char[f_name.length() + 1];
        string_to_char(f_name, file_name);
        string com = "echo %userprofile%>" + f_name;
        char* com_cmd = new char[com.length() + 1];
        string_to_char(com, com_cmd);
        system(com_cmd); // system("echo %userprofile%>user%date%.txt");
        delete[] com_cmd;
        ifstream file(file_name, std::ios::in);
        char ch;
        while (file)
        {
            ch = file.get();
            if (file && ch != 10) str += ch;
        }
        file.close();
        str = str + "\\Desktop\\Projects\\";
        com = "del " + f_name;
        com_cmd = new char[com.length() + 1];
        string_to_char(com, com_cmd);
        system(com_cmd); //system("del user%date%.txt");
        delete[] com_cmd;
        delete[] file_name;
        return str;
    }
    void Project_init() {
        string Project_list = get_Project_list();
        string name;
        int counter_1 = 0;
        int counter_2 = 0;
        for (int i = 0, j = 0, flag = 1; i < Project_list.length() && j < number_of_the_Projects; i++) {
            if (flag)
            {
                if (Project_list[i] == (int)32) {
                    counter_1 = i + 1;
                    flag = false;
                }
            }
            else
            {
                if ((Project_list[i] == (int)10) || (i == (Project_list.length() - 1) && Project_list[i] != (int)10))
                {
                    counter_2 = i - counter_1;
                    if (Project_list[i] != (int)10) counter_2++;
                    flag = true;
                    name = Project_list.substr(counter_1, counter_2);
                    prj[j].init_Project(j, name);
                    j++;
                }
            }
        }
        prj[number_of_the_Projects - 1].init_Project(number_of_the_Projects - 1, "ПУСТО");
    }
    void underline() {
        for (int i = 0; i < 50; i++)
        {
            Console += '-';
        }
        Console += '\n';
    }
    Shell()
    {
        WORK = true;
        //console_mode = true;
        set_rus_letters();
        set_console_size();
        // Написать проверку целлостности программы, наличие папок и файлов
        Prog_directory = get_Prog_directory();
        Project_directory = textfile_to_string("Prog_files\\Project_directory.txt");
        create_Project_directory();
        string Project_list = get_Project_list();
        if (Project_list == "\0")  number_of_the_Projects = 1;
        else number_of_the_Projects = get_number_of_the_Projects() + 1; // добавляется "1" под новый проект
        prj = new Project[number_of_the_Projects];
        Project_init();
        user_Project_directory = get_user_Project_directory();
        Console_init();
    }
    ~Shell()
    {
        delete[] prj;
    }
    void null_Console()
    {
        Console = "\0";
    }
    int Console_init()
    {
        null_Console();
        underline();
        Console = "Выбирете <ПУСТО> для создания нового проекта.\n";
        Console += "00. Выход из программы\n";
        Console_marker = (int)Console.length();
        underline();
        Console += "Быберете номер проекта и нажмите <ENTER>: ";
        return 0;
    }
    int Console_menu ()
    {
        Console += "Меню:\n";
        Console += "\t1 - PULL the project  - выгрузка проекта на ПК\n";
        Console += "\t2 - PUSH - загрузка проекта на сервер (В РАЗРАБОТКЕ)\n";
        Console += "\t3 - MODIFY - изменение проекта на севере(В РАЗРАБОТКЕ)\n";
        Console += "\t4 - DEL the Project - удалить проект с сервера\n";
        Console += "\t5 - <ПУСТО>\n";
        Console += "\t6 - <ПУСТО>\n";
        Console += "\t7 - <ПУСТО>\n";
        Console += "\t8 - <ПУСТО>\n";
        Console += "\t9 - возврат к <выбору проекта>\n";
        Console += "\t0 - Выход\n";
        underline();
        Console += "Быберете номер команды и нажмите <ENTER>: ";
        return 0;
    }
    void set_rus_letters() //#include <windows.h>
    {
        SetConsoleCP(1251); // включит "русский" язык
        SetConsoleOutputCP(1251); // включит "русский" язык
    }
    void set_console_size()
    {
        system("mode con cols=100 lines=50"); // устанавливает размер консоли
    }
    COORD coord;
    void gotoxy(int x, int y)
    {
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void show_Projects()
    {
        for (int i = 0; i < number_of_the_Projects; i++)
        {

            if (!prj[i].is_free())
            {
                SetTextColorFirst(White, Red);
                prj[i].show();
                SetTextColorFirst(White, Black);
            }
            else prj[i].show();
        }
    }
    void update_console ()
    {
        while (WORK)
        {
            set_console_size();
            gotoxy(0, 0);
            for (int i = 0; i < Console_marker; i++)
            {
                cout << Console[i];
            }
            show_Projects();
            for (int i = Console_marker; i < Console.length(); i++)
            {
                cout << Console[i];
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    void test_Shell() { cout << "*";}
    int exec()
    {
        thread console([&](){update_console();});
        while (WORK)
        {
            do
            {
                Active_project_number = (user_command_choose() - 1); // command_choose(); передает "машинный" номер проекта
                while (Active_project_number < 0 || Active_project_number > number_of_the_Projects - 1)
                {
                    if (Active_project_number < 0)
                    {
                        WORK = false;
                        console.detach();
                        return 0; // при вводе "0" программа штатно завершается
                    }
                    Active_project_number = user_command_choose() - 1;
                }
            } while (!prj[Active_project_number].is_free());
            if (prj[Active_project_number].get_Project_name() == "ПУСТО")
            {
                if (Active_project_number < (number_of_the_Projects - 1)) Del_the_empty_file(Active_project_number);
                Create_New_Project();
                console.detach();
                return 0; // При успешном создании нового проекта возвращается <0> для закрытия программы
            }
            else
            {
                prj[Active_project_number].create_stop_flag();
                //console_mode = false;
            }
            Console_menu();
            int com = user_command_choose();
            while (com > 9 || com < 0)
            {
                com = user_command_choose();
            }
            switch (com)
            {
                case (1):
                    Pull_the_Project();
                    break;
                case (2): // Разработка
                    prj[Active_project_number].delete_stop_flag();
                    Console_init();
                    break;
                case (3): // Разработка
                    prj[Active_project_number].delete_stop_flag();
                    Console_init();
                    break;
                case (4):
                    Del_the_Project();
                    prj[Active_project_number].delete_stop_flag();
                    Console_init();
                    break;
                case (5): // Разработка
                    prj[Active_project_number].delete_stop_flag();
                    Console_init();
                    break;
                case (6): // Разработка
                    prj[Active_project_number].delete_stop_flag();
                    Console_init();
                    break;
                case (7): // Разработка
                    prj[Active_project_number].delete_stop_flag();
                    Console_init();
                    break;
                case (8): // Разработка
                    prj[Active_project_number].delete_stop_flag();
                    Console_init();
                    break;
                case (9):
                    prj[Active_project_number].delete_stop_flag();
                    Console_init();
                    break;
                case (0):
                    prj[Active_project_number].delete_stop_flag();
                    WORK = false;
                    break;
                default: break;// штатно не должна происходить
            }
        }
        console.detach(); // отсоединение потока
        return 0;
    }
    void solve_the_Error(int err) {}; // В РАЗРАБОТККЕ
    string Project_name_input() // обеспечивает корректный ввод названия проекта и возвращает его название ввиде строки
    {
        string str = "\0";
        char ch = 0;
        int counter = 0; // от 0 - 255 <ограничение на длину имени файла>
        while (ch != 13)
        {
            ch = _getch();
            if (counter == 0) // Проверка первых символов
            {
                if (
                    (ch >= 48 && ch <= 57) || // 0 - 9
                    (ch == 32) || // <пробел>
                    (ch == 46) || // .
                    (ch == 44) || // ,
                    (ch == 40) || // (
                    (ch == 41) || // )
                    (ch == 45) || // -
                    (ch == 95) // _
                    ) ch = 0;
            }
            if (
                (ch >= 48 && ch <= 57) || // 0 - 9
                (ch >= 97 && ch <= 122) || // a - z
                (ch >= 65 && ch <= 90) || // A - Z
                (ch >= -64 && ch <= -1) || // A - я
                (ch == -72) || // ё
                (ch == -88) || // Ё
                (ch == 32) || // <пробел>
                (ch == 46) || // .
                (ch == 44) || // ,
                (ch == 40) || // (
                (ch == 41) || // )
                (ch == 45) || // -
                (ch == 95) // _
                )
            {
                if (counter < 255)
                {
                    cout << ch;
                    str += ch;
                    Console += ch; // Костыль для управления консолью
                    counter++;
                }
            }
            if (ch == 8 && counter > 0) // <backspace>
            {
                cout << "\b" << (char)32 << "\b";
                Console.pop_back(); // Костыль для управления консолью
                str.pop_back(); // удалить последний символ в строке
                counter--;
            }
            if (str.length() == 0) ch = 0;
        }
        if (str == "ПУСТО") str = "Empty_project";
        return (string)str;
    }
    int Create_New_Project() // создает новый проект, возвращает 0 при успешном завершении функции.
    {
        string new_Project_name = "\0";
        Console += "<Создание нового проекта>\n";
        underline();
        Console += "Введите название нового проекта и нажмите <ENTER>: ";
        new_Project_name += Project_name_input();
        prj[Active_project_number].set_Project_name(new_Project_name);
        new_Project_name = prj[Active_project_number].get_n_Project_name();
        Console += "\n";
        cout << endl;
        prj[Active_project_number].create_stop_flag();
        if (FileExists("Prog_files\\Create_new_folders_to the_new_project.txt"))
        {
            string list = textfile_to_string("Prog_files\\Create_new_folders_to the_new_project.txt");
            list = decode_function(list, Active_project_number);
            string_to_system_command(list);
        }
        else
        {
            solve_the_Error(1);
        }
        if (FileExists("Prog_files\\Push_the_templates_to_the_new_project.txt"))
        {
            string list = textfile_to_string("Prog_files\\Push_the_templates_to_the_new_project.txt");
            list = decode_function(list, Active_project_number);
            string_to_system_command(list);
        }
        else
        {
            solve_the_Error(1);
        }
        underline();
        Console += "Пустой проект < " + prj[Active_project_number].get_n_Project_name() + " > успешно создан.\n";
        underline();
        Console += "Вы хотите выгрузить его себе на ПК? (Y/N)";
        if (press_yn())
        {
            string str = textfile_to_string("Prog_files\\Push_the_project.txt");
            str = decode_function(str, Active_project_number);
            Console += "\nИдет копирование ...\n";
            string_to_system_command(str);
            Console += "Копирование завершено.\n";
            underline();
            press_any_key();
        }
        prj[Active_project_number].delete_stop_flag();
        return 0;
    }
    int Pull_the_Project() // выгружает активный проект в пользовательскую директорию с проектами
    {
        string str = textfile_to_string("Prog_files\\Push_the_project.txt");
        str = decode_function(str, Active_project_number);
        Console += "\nИдет копирование ...\n";
        string_to_system_command(str);
        Console += "Копирование завершено.\n";
        underline();
        press_any_key();
        prj[Active_project_number].delete_stop_flag();
        return 0;
    }
    int Del_the_Project() // удаляет проект
    {
        string str = textfile_to_string("Prog_files\\Del_the_project.txt");
        str = decode_function(str, Active_project_number);
        Console += "\nИдет удаление ...\n";
        string_to_system_command(str);
        Console += "удаление завершено.\n";
        prj[Active_project_number].delete_stop_flag();
        prj[Active_project_number].set_Project_name("ПУСТО");
        str = "md \"" + Project_directory + prj[Active_project_number].get_n_Project_name() + "\"";
        string_to_system_command(str);
        int counter = number_of_the_Projects - 2;
        for (int i = counter; i > -1; i--)
        {
            if (prj[i].get_Project_name() == "ПУСТО")
            {
                Del_the_empty_file(i + 1);
                number_of_the_Projects--;
            }
            else break;
        }
        underline();
        press_any_key();
        return 0;
    }
    int Del_the_empty_file (int number) // удаляет папку с назвнием "Х. ПУСТО"
    {
        string str = "\0";
        if (number < 10)  str = "rd /s /q \"" + Project_directory + "0" + std::to_string(number) + ". ПУСТО\"";
        else  str = "rd /s /q \"" + Project_directory + std::to_string(number) + ". ПУСТО\"";
        string_to_system_command(str);
        return 0;
    }
    int new_prog_version() // возвращает 0 при успешном создании новой версии
    {
        string prog_workspace_dir_AP = Prog_directory + "prog_workspace\\" + prj[Active_project_number].get_n_Project_name(); // AP - Active project
        string project_dir_AP = Project_directory + prj[Active_project_number].get_n_Project_name();
        string CV_report_file = prog_workspace_dir_AP + "\\Current_version.txt"; // CV - Current version
        fstream file(CV_report_file, std::ios::in | std::ios::out);
        if (!file)
        {
            cout << "Обработчик ошибки, которого пока нет. Файл " << prog_workspace_dir_AP << " открыть не получилось";
            exit(1);
        }
        int Current_version;
        file >> Current_version;
        file.clear();
        file.seekp(0, std::ios::beg);
        if (!file)
        {
            cout << "Обработчик ошибки, которого пока нет. Файл " << prog_workspace_dir_AP << " открыть не получилось";
            exit(1);
        }
        string project;
        SYSTEMTIME time;
        GetSystemTime(&time); //  std::to_string(time.wMilliseconds)
        string repot_tail = "\\V" + std::to_string(Current_version + 1) + ".txt";
        string report = prog_workspace_dir_AP + repot_tail;
        string tempo_report = prog_workspace_dir_AP + "\\tempo" + std::to_string(time.wMilliseconds);
        string com = "dir /b /s \"" + project_dir_AP + "\">\"" + tempo_report + "\"";
        string_to_system_command(com);
        fstream tempo_file(tempo_report, std::ios::out | std::ios::in);
        fstream file_report(report, std::ios::out);
        char ch;
        file_report << (Current_version + 1) << "\n";
        string file_name = "\0";
        while (tempo_file)
        {
            tempo_file.get(ch);
            if (tempo_file)
            {
                if (ch == '\n')
                {
                    if (!unimportant_folders(file_name))
                    {
                        if (FileExists(file_name))
                        {
                            file_report << file_name << endl;
                            file_report << file_hash(file_name) << endl;
                        }
                    }
                    file_name = "\0";
                }
                else
                {
                    file_name += ch;
                }
            }
        }
        file << Current_version + 1;
        file.close();
        tempo_file.close();
        file_report.close();
        delete_file(tempo_report);
        return 0;
    }
    string get_string_line(string str, int n) //  возвращает строку, номер которой получает (нумерация с нуля)
    {
        int length = (int)str.length();
        if (n < 0 || length == 0) return "\0";
        string s = "\0";
        if (n == 0)
        {
            for (int i = 0; i < length; i++)
            {
                if (str[i] != '\n') s += str[i];
                else break;
            }
        }
        else
        {
            int counter = 0;
            for (int i = 0; i < length; i++)
            {
                if (str[i] == '\n') counter++;
                if (counter == n)
                {
                    counter = i + 1;
                    break;
                }
            }
            for (int i = counter; i < length; i++)
            {
                if (str[i] != '\n') s += str[i];
                else break;
            }
        }
        return s;
    }
    string file_hash(string file_name) // возвращает хэш-сумму файла
    {
        //#include <chrono>
        string hash;
        SYSTEMTIME time;
        GetSystemTime(&time);
        string file_report = file_name + std::to_string(time.wMilliseconds) + ".txt";
        string com = "certutil -hashfile \"" + file_name + "\">\"" + file_report + "\"";
        string_to_system_command(com);
        string s = textfile_to_string(file_report);
        hash = get_string_line(s, 1);
        com = "del \"" + file_report + "\"";
        string_to_system_command(com);
        return hash;
    }
    int press_yn()
    {
        SetConsoleCP(1251); // включит "русский" язык
        SetConsoleOutputCP(1251); // включит "русский" язык
        int ch;
        while (1)
        {
            // в русской раскладке Y (205), y (237), N (210), n(242)
            ch = _getch();
            if (ch == 'Y' || ch == 'y' || ch == 205 || ch == 237) return 1;
            if (ch == 'N' || ch == 'n' || ch == 210 || ch == 242) return 0;
        }
    }
    void press_any_key()
    {
        Console += "Для продолжения нажмите любую клавишу  ";
        int ch = _getch();
    }
    int unimportant_folders(string file_name) // отсекает папки с болтами и старыми версиями
    {
        int length = file_name.length();
        char ch = 0;
        size_t pos = file_name.find("ru-RU");
        if (pos != std::string::npos)
        {
            return 1;
        }
        pos = file_name.find("OldVersions");
        if (pos != std::string::npos)
        {
            return 1;
        }
        return 0;
    }
    void delete_file(string file_name)
    {
        char* f_name = new char[file_name.length() + 1];
        string_to_char(file_name, f_name);
        std::remove(f_name);
        delete[] f_name;
    }
    int user_command_choose() {
        string str = "\0";
        char ch;
        int counter = 0;
        do {
            ch = _getch();
            if (ch < 0) continue; // защита от "русских" символов
            if (isdigit(ch)) {
                if (counter > 5) continue;
                cout << ch;
                Console += ch; // Костыль для управления консолью
                str += ch;
                counter++;
            }
            else {
                if ((ch == 8) && (counter > 0)) {
                    cout << "\b" << (char)32 << "\b";
                    Console.pop_back();; // Костыль для управления консолью
                    str.pop_back(); // удалить последний символ в строке
                    counter--;
                }
            }
            if (counter == 0) ch = 0;
        } while (ch != 13);
        for (int i = 0; i < counter; i++)
        {
            cout << "\b" << (char)32 << "\b";
            Console.pop_back();
        }
        return std::stoi(str);
    }
};
#endif // PDM_H
