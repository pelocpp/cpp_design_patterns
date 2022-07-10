// ===========================================================================
// ConceptualExample.cpp // Type Erasure
// ===========================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace ConceptualExample
{
    namespace Motivation01
    {
        class Animal
        {
        public:
            virtual std::string see() const = 0;
            virtual std::string say() const = 0;
        };

        class Cow : public Animal
        {
        public:
            std::string see() const { return "cow"; }
            std::string say() const { return "moo"; }
        };

        class Pig : public Animal
        {
        public:
            std::string see() const { return "pig"; }
            std::string say() const { return "oink"; }
        };

        class Dog : public Animal
        {
        public:
            std::string see() const { return "dog"; }
            std::string say() const { return "woof"; }
        };

        void seeAndSay(const std::shared_ptr<Animal> animal)
        {
            std::cout
                << "The " << animal->see() << " says '"
                << animal->say() << "' :)." << std::endl;
        }

        void clientCode()
        {
            std::shared_ptr<Animal> aCow{ std::make_shared<Cow>() };
            std::shared_ptr<Animal> aPig{ std::make_shared<Pig>() };
            std::shared_ptr<Animal> aDog{ std::make_shared<Dog>() };

            seeAndSay(aCow);
            seeAndSay(aPig);
            seeAndSay(aDog);
        }
    }

    namespace Motivation02
    {
        template <typename T>
        void seeAndSay(const std::shared_ptr<T> animal)
        {
            std::cout
                << "The " << animal->see() << " says '"
                << animal->say() << "' :)." << std::endl;
        }

        class Dog
        {
        public:
            std::string see() const { return "dog"; }
            std::string say() const { return "woof"; }
        };

        void clientCode()
        {
            std::shared_ptr<Dog> aDog{ std::make_shared<Dog>() };
            seeAndSay<Dog>(aDog);
        }
    }

    namespace Motivation03
    {
        class MyAnimal
        {
        public:
            virtual std::string see() const = 0;
            virtual std::string say() const = 0;
        };

        class Cow
        {
        public:
            std::string see() const { return "cow"; }
            std::string say() const { return "moo"; }
        };

        class Pig
        {
        public:
            std::string see() const { return "pig"; }
            std::string say() const { return "oink"; }
        };

        class Dog
        {
        public:
            std::string see() const { return "dog"; }
            std::string say() const { return "woof"; }
        };

        class MyCow : public MyAnimal
        {
        private:
            Cow m_cow;

        public:
            virtual std::string see() const override { return m_cow.see(); }
            virtual std::string say() const override { return m_cow.say(); }
        };

        class MyPig : public MyAnimal
        {
        private:
            Pig m_pig;

        public:
            virtual std::string see() const override { return m_pig.see(); }
            virtual std::string say() const override { return m_pig.say(); }
        };

        class MyDog : public MyAnimal
        {
        private:
            Dog m_dog;

        public:
            virtual std::string see() const override { return m_dog.see(); }
            virtual std::string say() const override { return m_dog.say(); }
        };

        void seeAndSay(const std::shared_ptr<MyAnimal> animal)
        {
            std::cout
                << "The " << animal->see() << " says '"
                << animal->say() << "' :)." << std::endl;
        }

        void clientCode()
        {
            std::shared_ptr<MyAnimal> aCow{ std::make_shared<MyCow>() };
            std::shared_ptr<MyAnimal> aPig{ std::make_shared<MyPig>() };
            std::shared_ptr<MyAnimal> aDog{ std::make_shared<MyDog>() };

            std::vector<std::shared_ptr<MyAnimal>> animals = { aCow , aPig , aDog };

            for (const auto& animal : animals) {
                seeAndSay(animal);
            }
        }
    }

    namespace Motivation04
    {
        class MyAnimal
        {
        public:
            virtual std::string see() const = 0;
            virtual std::string say() const = 0;
        };

        class Cow
        {
        public:
            std::string see() const { return "cow"; }
            std::string say() const { return "moo"; }
        };

        class Pig
        {
        public:
            std::string see() const { return "pig"; }
            std::string say() const { return "oink"; }
        };

        class Dog
        {
        public:
            std::string see() const { return "dog"; }
            std::string say() const { return "woof"; }
        };

        template <typename T>
        class AnimalWrapper : public MyAnimal
        {
        private:
            const T& m_animal;

        public:
            AnimalWrapper(const T& animal) : m_animal{ animal } {}

            virtual std::string see() const override { return m_animal.see(); }
            virtual std::string say() const override { return m_animal.say(); }
        };

        void seeAndSay(const std::shared_ptr<MyAnimal> animal)
        {
            std::cout
                << "The " << animal->see() << " says '"
                << animal->say() << "' :)." << std::endl;
        }

        void clientCode()
        {
            std::shared_ptr<MyAnimal> spCow{ std::make_shared<AnimalWrapper<Cow>>(Cow{}) };
            std::shared_ptr<MyAnimal> spPig{ std::make_shared<AnimalWrapper<Pig>>(Pig{}) };
            std::shared_ptr<MyAnimal> spDog{ std::make_shared<AnimalWrapper<Dog>>(Dog{}) };

            std::vector<std::shared_ptr<MyAnimal>> animals = { spCow , spPig , spDog };

            for (const auto& animal : animals) {
                seeAndSay(animal);
            }
        }
    }

    namespace Motivation05
    {
        class Cow
        {
        public:
            std::string see() const { return "cow"; }
            std::string say() const { return "moo"; }
        };

        class Pig
        {
        public:
            std::string see() const { return "pig"; }
            std::string say() const { return "oink"; }
        };

        class Dog
        {
        public:
            std::string see() const { return "dog"; }
            std::string say() const { return "woof"; }
        };

        class SeeAndSay
        {
            // 'interface'
            class MyAnimal
            {
            public:
                virtual std::string see() const = 0;
                virtual std::string say() const = 0;
            };

            // derived type(s) / 'wrapper class'
            template <typename T>
            class AnimalWrapper : public MyAnimal
            {
            private:
                const T& m_animal;

            public:
                AnimalWrapper(const T& animal) : m_animal{ animal } {}

                virtual std::string see() const override { return m_animal->see(); }
                virtual std::string say() const override { return m_animal->say(); }
            };

            // registered animals
            std::vector<std::shared_ptr<MyAnimal>> m_animals;

        public:
            template <typename T>
            void addAnimal(const T& animal)
            {
                m_animals.push_back(std::make_shared<AnimalWrapper<T>>(animal));
            }

            void seeAndSay(const std::shared_ptr<MyAnimal> animal) {
                std::cout
                    << "The " << animal->see() << " says '"
                    << animal->say() << "' :)." << std::endl;
            }

            void print() {
                for (const auto& animal : m_animals) {
                    seeAndSay(animal);
                }
            }
        };

        void clientCode()
        {
            SeeAndSay animals;

            std::shared_ptr<Cow> aCow{ std::make_shared<Cow>() };
            std::shared_ptr<Pig> aPig{ std::make_shared<Pig>() };
            std::shared_ptr<Dog> aDog{ std::make_shared<Dog>() };

            animals.addAnimal(aCow);
            animals.addAnimal(aPig);
            animals.addAnimal(aDog);

            animals.print();
        }
    }

    namespace Motivation06
    {
        class Cow
        {
        public:
            std::string see() const { return "cow"; }
            std::string say() const { return "moo"; }
        };

        class Pig
        {
        public:
            std::string see() const { return "pig"; }
            std::string say() const { return "oink"; }
        };

        class Dog
        {
        public:
            std::string see() const { return "dog"; }
            std::string say() const { return "woof"; }
        };

        class SeeAndSay
        {
            // 'interface'
            class AnimalConcept
            {
            public:
                virtual std::string see() const = 0;
                virtual std::string say() const = 0;
            };

            // derived type(s)
            template <typename T>
            class AnimalModel : public AnimalConcept
            {
            private:
                const T& m_animal;

            public:
                AnimalModel(const T& animal) : m_animal{ animal } {}

                virtual std::string see() const override { return m_animal->see(); }
                virtual std::string say() const override { return m_animal->say(); }
            };

            // registered animals
            std::vector<std::shared_ptr<AnimalConcept>> m_animals;

        public:
            template <typename T>
            void addAnimal(const T& animal)
            {
                m_animals.push_back(std::make_shared<AnimalModel<T>>(animal));
            }

            void seeAndSay(const std::shared_ptr<AnimalConcept> animal) {
                std::cout
                    << "The " << animal->see() << " says '"
                    << animal->say() << "' :)." << std::endl;
            }

            void print() {
                for (const auto& animal : m_animals) {
                    seeAndSay(animal);
                }
            }
        };

        void clientCode()
        {
            SeeAndSay animals;

            std::shared_ptr<Cow> aCow{ std::make_shared<Cow>() };
            std::shared_ptr<Pig> aPig{ std::make_shared<Pig>() };
            std::shared_ptr<Dog> aDog{ std::make_shared<Dog>() };

            animals.addAnimal(aCow);
            animals.addAnimal(aPig);
            animals.addAnimal(aDog);

            animals.print();
        }
    }
}

void test_conceptual_example()
{
    ConceptualExample::Motivation01::clientCode();
    ConceptualExample::Motivation02::clientCode();
    ConceptualExample::Motivation03::clientCode();
    ConceptualExample::Motivation04::clientCode();
    ConceptualExample::Motivation05::clientCode();
    ConceptualExample::Motivation06::clientCode();
}

// ===========================================================================
// End-of-File
// ===========================================================================
