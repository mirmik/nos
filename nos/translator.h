#ifndef NOS_TRANSLATOR_H
#define NOS_TRANSLATOR_H

#include <string>

namespace nos
{
    class ITranslator
    {
    public:
        virtual ~Translator() = default;
        virtual std::string translate(const std::string &text) = 0;
    };

    class Translator : public ITranslator
    {
        std::unordered_map<std::string, std::string> translations;

    public:
        std::string translate(const std::string &text) override
        {
            auto it = translations.find(text);
            if (it != translations.end())
            {
                return it->second;
            }
            return text;
        }
    };

    class TranslateManager
    {
        std::unordered_map<std::string, std::unique_ptr<ITranslator>>
            translators;
        std::string currentLanguage;

    public:
        void addTranslator(const std::string &language,
                           std::unique_ptr<ITranslator> translator)
        {
            translators[language] = std::move(translator);
        }

        void setLanguage(const std::string &language)
        {
            currentLanguage = language;
        }

        std::string translate(const std::string &text)
        {
            auto it = translators.find(currentLanguage);
            if (it != translators.end())
            {
                return it->second->translate(text);
            }
            return text;
        }

        static TranslateManager &instance()
        {
            static TranslateManager instance;
            return instance;
        }
    };
}

#endif