//
// Created by arman on 11/4/22.
//
class iServerManager {
    virtual bool cardRegistration() = 0;
    virtual bool cardCheck() = 0;
    virtual double getBalance() = 0;
    virtual bool cash_in() = 0;
    virtual bool cash_out() = 0;

};