#ifndef IDENTIFIERGENERATOR_HPP
#define IDENTIFIERGENERATOR_HPP

template <typename Tag, typename IdType>
struct IdentifierGenerator
{
        IdType operator()() {
                return m_value++;
        }
        IdentifierGenerator() : m_value() {}
        IdType m_value;
};

struct IdentifierGeneratorDefaultTag {};

template <typename Tag = IdentifierGeneratorDefaultTag, typename IdType = int>
IdType generateId()
{
        static IdentifierGenerator<Tag, IdType> s_generator;
        return s_generator();
}

#endif // IDENTIFIERGENERATOR_HPP
