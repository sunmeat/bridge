#include <iostream>
using namespace std;

// Абстрактный базовый класс устройства
class Device {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual bool isOn() = 0; // метод для проверки включено ли устройство
    virtual void setVolume(int volume) = 0;
    virtual void changeChannel(int channel) = 0;
    virtual ~Device() {}
};

// Конкретный класс радио
class Radio : public Device {
    bool on = false;
    int volume = 50;
    int channel = 1;

public:
    void turnOn() override {
        cout << "Radio is turned on\n";
        on = true;
    }

    void turnOff() override {
        cout << "Radio is turned off\n";
        on = false;
    }

    bool isOn() override {
        return on;
    }

    void setVolume(int volume) override {
        this->volume = volume;
        cout << "Radio volume is set to " << volume << "\n";
    }

    void changeChannel(int channel) override {
        this->channel = channel;
        cout << "Radio channel is set to " << channel << "\n";
    }
};

// Конкретный класс телевизора
class TV : public Device {
    bool on = false;
    int volume = 50;
    int channel = 1;

public:
    void turnOn() override {
        cout << "TV is turned on\n";
        on = true;
    }

    void turnOff() override {
        cout << "TV is turned off\n";
        on = false;
    }

    bool isOn() override {
        return on;
    }

    void setVolume(int volume) override {
        this->volume = volume;
        cout << "TV volume is set to " << volume << "\n";
    }

    void changeChannel(int channel) override {
        this->channel = channel;
        cout << "TV channel is set to " << channel << "\n";
    }
};

// Конкретный класс Кондиционера
class AirConditioner : public Device {
    bool on = false;
    int temperature = 25;
    int mode = 0;

public:
    void turnOn() override {
        cout << "Air conditioner is turned on\n";
        on = true;
    }

    void turnOff() override {
        cout << "Air conditioner is turned off\n";
        on = false;
    }

    bool isOn() override {
        return on;
    }

    void setVolume(int temperature) override {
        this->temperature = temperature;
        cout << "Air conditioner temperature is set to " << temperature << "\n";
    }

    void changeChannel(int mode) override {
        this->mode = mode;
        cout << "Air conditioner mode is set to " << mode << "\n";
    }
};

// Конкретный класс Освещения в комнате
class RoomLight : public Device {
    bool on = false;
    int brightness = 50;

public:
    void turnOn() override {
        cout << "Room light is turned on\n";
        on = true;
    }

    void turnOff() override {
        cout << "Room light is turned off\n";
        on = false;
    }

    bool isOn() override {
        return on;
    }

    void setVolume(int brightness) override {
        this->brightness = brightness;
        cout << "Room light brightness is set to " << brightness << "\n";
    }

    void changeChannel(int) override {}
};

// Абстрактный базовый класс пульта
class Remote {
public:
    virtual void power() = 0;
    virtual ~Remote() {}
};

// Конкретный класс простого пульта
class BasicRemote : public Remote {
protected:
    Device* device;

public:
    BasicRemote(Device* device) : device(device) {}

    void power() override {
        if (device->isOn()) {
            device->turnOff();
        }
        else {
            device->turnOn();
        }
    }
};

// Конкретный класс продвинутого пульта
class AdvancedRemote : public BasicRemote {
public:
    AdvancedRemote(Device* device) : BasicRemote(device) {}

    void mute() {
        device->setVolume(0);
    }
};

int main() {
    Device* device = new TV();
    Remote* remote = new BasicRemote(device);
    remote->power();
    delete device;
    delete remote;

    device = new AirConditioner();
    remote = new BasicRemote(device);
    remote->power();
    ((AirConditioner*)(device))->setVolume(20);
    ((AirConditioner*)(device))->changeChannel(1);
    remote->power();

    delete device;
    delete remote;
}

/*
В коде используется паттерн "Мост" (Bridge), который
разделяет абстракцию и реализацию таким образом, чтобы
они могли изменяться независимо друг от друга. В данном
случае, абстракция представлена классами Device и Remote,
а реализация - классами Radio, TV, AirConditioner и
RoomLight. Классы BasicRemote и AdvancedRemote являются
различными реализациями абстракции Remote.

Классы устройств являются конкретными реализациями
абстрактного базового класса Device. Каждый конкретный
класс имеет методы для включения и выключения устройства,
проверки статуса, установки громкости и переключения
каналов (или температуры и режима в случае кондиционера).

Классы пультов наследуются от абстрактного базового
класса Remote. BasicRemote - это простой пульт, который
может включать и выключать устройство, а AdvancedRemote
- это продвинутый пульт, который наследует все
функциональные возможности простого пульта и также имеет
метод mute(), который устанавливает громкость на ноль.

В main() создаются объекты устройств и соответствующие
им пульты, которые используются для включения и
выключения устройств.
*/

// https://refactoring.guru/ru/design-patterns/bridge

/*
Мост — это структурный паттерн проектирования, который
разделяет один или несколько классов на две отдельные
иерархии — абстракцию и реализацию, позволяя изменять
их независимо друг от друга.
*/