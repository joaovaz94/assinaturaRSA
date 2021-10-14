#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <vector>
#include <string>
#include <cstring>

class ByteArray {

    public:

        typedef std::vector<unsigned char>::const_iterator const_iterador;

        explicit ByteArray(size_t tamanho);
        explicit ByteArray(const std::string& s);
        ByteArray(const char* c, size_t n);
        ByteArray(const unsigned char* c, size_t t);
        ByteArray(const std::vector<unsigned char>& data);

        const unsigned char* recebeConteudoPonteiro() const;
        unsigned char* recebeConteudoPonteiro();

        void defineConteudoPonteiro(unsigned char* cont, unsigned int tamanho);

        const std::vector<unsigned char>& recebeVetor() const;
        std::vector<unsigned char>& recebeVetor();

        size_t size() const;

        bool ehVazio() const;

        void reserve(size_t tamanho);
        void resize(size_t tamanho);
        void resize(size_t tamanho, char c);

        ByteArray& operator+=(const ByteArray& b);
        ByteArray& operator+=(char c);

        ByteArray & operator^=(const ByteArray& p);
        const ByteArray operator^(const ByteArray& p);        

        const unsigned char& operator[](size_t i) const;
        unsigned char& operator[](size_t i);

        const_iterador begin() const;
        const_iterador end() const;

        std::string toString() const;

        void clear();

        const std::vector<unsigned char>& recebeConteudoVetor() const;

        void salvaEmArquivo(const std::string& onde) const;

        static ByteArray criaDeArquivo(const std::string& arquivo);
        static std::vector<unsigned char> cria(const std::string& s);
        static std::vector<unsigned char> cria(const char* c);
        static std::vector<unsigned char> cria(const unsigned char* c, size_t n);
        static std::vector<unsigned char> cria(const char* c, size_t n);

        static const unsigned char* dado(const std::vector<unsigned char>& v);

        static const char* dadoChar(const std::vector<unsigned char>& v);

        std::string praHex(bool ehMaiusculo = true) const;
        std::string praHex(char separador, bool ehMaiusculo = true) const;

        friend ByteArray operator+(const ByteArray& a, const ByteArray& b) {
            ByteArray resultado(a);
            resultado.dado_.insert(resultado.dado_.end(), b.dado_.begin(), b.dado_.end());
            return resultado;
        }

        friend ByteArray operator+(const ByteArray& a, char b) {
            ByteArray x(1);
            x[0] = static_cast<unsigned char>(b);
            return a + x;
        }

        friend bool operator==(const ByteArray& a, const ByteArray& b) {
            return a.dado_ == b.dado_;
        }

    private:
    
        std::vector<unsigned char> dado_;
};

inline ByteArray::ByteArray(size_t tamanho) :
                dado_(tamanho)
{
}


inline ByteArray::ByteArray(const std::string& s) :
                dado_(s.begin(), s.end())
{
}

inline ByteArray::ByteArray(const char* c, size_t n) {
    if (n > 0) {
        dado_.resize(n);
        memcpy(&dado_[0], c, n);
    }
}

inline ByteArray::ByteArray(const unsigned char* c, size_t t) {
    if (t > 0) {
        dado_.resize(t);
        memcpy(&dado_[0], c, t);
    }
}

inline ByteArray::ByteArray(const std::vector<unsigned char>& dado) :
                dado_(dado)
{
}

inline const unsigned char* ByteArray::recebeConteudoPonteiro() const {
    return dado_.empty() ? nullptr : &dado_[0];
}

inline unsigned char* ByteArray::recebeConteudoPonteiro() {
    return dado_.empty() ? nullptr : &dado_[0];
}

inline void ByteArray::defineConteudoPonteiro(unsigned char* cont, unsigned int tamanho) {
    this->clear();
    this->resize(tamanho);
    memcpy(&dado_[0], cont, tamanho);
}

inline const std::vector<unsigned char>& ByteArray::recebeVetor() const {
    return dado_;
}

inline std::vector<unsigned char>& ByteArray::recebeVetor() {
    return dado_;
}

inline size_t ByteArray::size() const {
    return dado_.size();
}

inline bool ByteArray::ehVazio() const {
    return dado_.empty();
}

inline void ByteArray::reserve(size_t tamanho) {
    dado_.reserve(tamanho);
}

inline void ByteArray::resize(size_t tamanho) {
    return dado_.resize(tamanho);
}

inline void ByteArray::resize(size_t tamanho, char c) {
    return dado_.resize(tamanho, static_cast<unsigned char>(c));
}

inline ByteArray& ByteArray::operator+=(const ByteArray& b) {
    dado_.insert(dado_.end(), b.dado_.begin(), b.dado_.end());
    return *this;
}

inline ByteArray& ByteArray::operator+=(char c) {
    dado_.push_back(static_cast<unsigned char>(c));
    return *this;
}

inline ByteArray & ByteArray::operator^=(const ByteArray& p) {
    std::vector<unsigned char> resultado = std::vector<unsigned char>(dado_);
    size_t ktam = p.dado_.size();
    size_t vtam = dado_.size();
    size_t k = 0;
    size_t v = 0;
    for (; v < vtam; v++) {
        resultado[v] = dado_[v] ^ p.dado_[k];
        k = (++k < ktam ? k : 0);
    }
    this->dado_ = resultado;
    return *this;
}

inline const ByteArray ByteArray::operator^(const ByteArray& p) {
    ByteArray resultado = *this;
    resultado ^= p;
    return resultado;
}

inline const unsigned char& ByteArray::operator[](size_t i) const {
    return dado_[i];
}

inline unsigned char& ByteArray::operator[](size_t i) {
    return dado_[i];
}

inline ByteArray::const_iterador ByteArray::begin() const {
    return dado_.begin();
}

inline ByteArray::const_iterador ByteArray::end() const {
    return dado_.end();
}

inline void ByteArray::clear() {
    dado_.clear();
}

inline const std::vector<unsigned char>& ByteArray::recebeConteudoVetor() const {
    return dado_;
}

inline const unsigned char* ByteArray::dado(const std::vector<unsigned char>& v) {
    return v.empty() ? nullptr : &v[0];
}

inline const char* ByteArray::dadoChar(const std::vector<unsigned char>& v) {
    return v.empty() ? nullptr : reinterpret_cast<const char*>(&v[0]);
}

#endif /*BYTEARRAY_H*/