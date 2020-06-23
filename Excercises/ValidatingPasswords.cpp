#include <iostream>
#include <string>
#include <string_view>
#include <cassert>

// resembles 'Component'
class PasswordValidator
{
public:
    virtual bool validate(std::string password) const = 0;
    virtual ~PasswordValidator() {}
};

// resembles 'ConcreteComponent'
class LengthValidator final : public PasswordValidator
{
private:
    unsigned int m_length; 

public:
    LengthValidator(unsigned int minLength) : m_length(minLength) {}

    bool validate(std::string password) const override {
        return password.length() >= m_length;
    }
};

// resembles 'DecoratorBase'
class PasswordValidatorDecorator : public PasswordValidator
{
private:
    std::unique_ptr<PasswordValidator> m_inner;

public:
    explicit PasswordValidatorDecorator(std::unique_ptr<PasswordValidator> validator)
        : m_inner(std::move(validator)) {}

    bool validate(std::string password) const override {
        return m_inner->validate(password);
    }
};

// resembles 'ConcreteDecorator'
class DigitPasswordValidator final : public PasswordValidatorDecorator
{
public:
    explicit DigitPasswordValidator(std::unique_ptr<PasswordValidator> validator) 
        : PasswordValidatorDecorator(std::move(validator)) {}

    bool validate(std::string password) const override {
        if (!PasswordValidatorDecorator::validate(password))
            return false;

        return password.find_first_of("0123456789") != std::string::npos;
    }
};

// resembles 'ConcreteDecorator'
class CasePasswordValidator final : public PasswordValidatorDecorator
{
public:
    explicit CasePasswordValidator(std::unique_ptr<PasswordValidator> validator)
        : PasswordValidatorDecorator(std::move(validator)) {}

    bool validate(std::string password) const override {
        if (!PasswordValidatorDecorator::validate(password))
            return false;

        bool haslower = false;
        bool hasupper = false;
        for (size_t i = 0; i < password.length() && !(hasupper && haslower);
            ++i)
        {
            if (islower(password[i])) haslower = true;
            else if (isupper(password[i])) hasupper = true;
        }
        return haslower && hasupper;
    }
};

// resembles 'ConcreteDecorator'
class SymbolPasswordValidator final : public PasswordValidatorDecorator
{
public:
    explicit SymbolPasswordValidator(std::unique_ptr<PasswordValidator> validator)
        : PasswordValidatorDecorator(std::move(validator)) {}

    bool validate(std::string password) const override {
        if (!PasswordValidatorDecorator::validate(password))
            return false;

        return password.find_first_of("!@#$%^&*(){}[]?<>") != std::string::npos;
    }
};

void validating_passwords() {

    std::unique_ptr<DigitPasswordValidator> validator1 =
        std::make_unique<DigitPasswordValidator>(
            std::make_unique<LengthValidator>(8));

    bool valid = validator1->validate("abc123!@#");
    assert(valid == true);

    valid = validator1->validate("abcde!@#");
    assert(valid == false);

    std::unique_ptr<SymbolPasswordValidator> validator2 =
        std::make_unique<SymbolPasswordValidator>(
            std::make_unique<CasePasswordValidator>(
                std::make_unique<DigitPasswordValidator>(
                    std::make_unique<LengthValidator>(8))));

    valid = validator2->validate("Abc123!@#");
    assert(valid == true);

    valid = validator2->validate("Abc123567");
    assert(valid == false);

    std::cout << "Done." << std::endl;
}
