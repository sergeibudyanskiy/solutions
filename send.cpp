// Example program
#include <iostream>
#include <string>
#include <memory>

class Command
{
    public:
        Command()
        {
            std::cout << "Command named ";
        }
        virtual ~Command()
        {
            std::cout << "deleted.\n";
        }
        virtual std::string getCommand() const = 0;
        
    protected:
        std::string cmd;
};

class ClientCommand : public Command // команды подключения/отключения клиента, начало/конец хода клиента
{
    public:
        ClientCommand(std::string str)
        {
            this->cmd = str;
            std::cout << "\"ClientCommand\" was created.\n";
        }
        ~ClientCommand()
        {
            std::cout << "Command named \"ClientCommand\" was ";
        }
        std::string getCommand() const
        {
            return this->cmd;
        }
};

class UnitCommand : public Command // команды атаковать юнитом, двигать юнитом, строить юнитом
{
    public:
        UnitCommand(std::string str)
        {
            this->cmd = str;
            std::cout << "\"UnitCommand\" was created.\n";
        }
        ~UnitCommand()
        {
            std::cout << "Command named \"UnitCommand\" was ";
        }
        std::string getCommand() const
        {
            return this->cmd;
        }
};

class ChatCommand : public Command // для всех остальных команд (сообщения)
{
    public:
        ChatCommand(std::string str)
        {
            this->cmd = str;
            std::cout << "\"ChatCommand\" was created.\n";
        }
        ~ChatCommand()
        {
            std::cout << "Command named \"ChatCommand\" was ";
        }
        std::string getCommand() const
        {
            return this->cmd;
        }
};

void send(std::unique_ptr<Command>& c) // якобы функция отправки команды на сервер
{
    std::cout << c->getCommand() << " - sended.\n";
}

void deleteSpaces(std::string& str) // удаление провелов с начала/конца строки
{
    size_t begin = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');
    str.erase(end + 1, str.size() - end);
    str.erase(0, begin);
}

Command* determineCommandType(std::string str) // отпределить по строке тип команды
{
    deleteSpaces(str);   
    if(str.find("connected") == 0 || str.find("unconnected") == 0 || str.find("play") == 0 || str.find("pause") == 0) return new ClientCommand(str);
    if(str.find("move") == 0 || str.find("attack") == 0 || str.find("build") == 0) return new UnitCommand(str);
    else return new ChatCommand(str);
}

int main()
{
    std::string str = "connected";
    do
    {
        if(str.empty())                     
        {
            std::cout << "> ";              
            std::getline(std::cin, str);                            // вводим команду
        }                                                           // определяем тип команды по ключевым словам
        std::unique_ptr<Command> cmd(determineCommandType(str));    // указатель нужен для реализации предотвращения утечки памяти и принцыпа
        send(cmd);                                                  // (создали команду - отправили - удалили команду)
        str.clear();                                                
    }
    while(true);
}
