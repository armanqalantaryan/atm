# ATM

Simple Client-Server ATM application implemented in C++. 

## Requirements

- Compiler with C++11 support
- Make
- Linux

## Description
Both of Server and Client are Single-threaded applications.
Server uses sqlite3 db to store the data.
Client works with one server by TCP protocol and uses 'receiveMessage' method to listen events.
Client works with interactive menus.

## Build with terminal
```bash
make (in project directory(ATM))
cd ./bin
```

## Run in terminal

```bash
cd ./bin (in project directory(ATM))
# runs 'Server'
./Server

# runs 'Client'
./Client
```

## Usage

First of all you need to run the Server. When server is already running, you need to run the Client as well. If everything is ok, you should get the following result:
```bash
New card registration, press 1
Enter card number, press 2
```
You should choose the option you need and continue with the chain.