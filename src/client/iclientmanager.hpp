
class iClientManager
{
    public:
    virtual bool process_registration() = 0;
    virtual bool process_card() = 0;
    virtual bool cash_in(int) = 0;
    virtual bool cash_out(int) = 0;
    virtual double get_balance() = 0;
    virtual ~iClientManager();
};
