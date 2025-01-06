#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Abstract Specification class
template <typename T>
class Specification {
public:
    virtual ~Specification() = default;
    virtual bool isSatisfied(const std::shared_ptr<T>& product) const = 0;
};

// Abstract Product class
template <typename T>
class Product {
protected:
    std::string name; // Name of the product

public:
    Product(const std::string& n) : name(n) {}
    virtual ~Product() = default;
    virtual T getSpecification() const = 0; // Pure virtual function
    virtual std::string getName() const = 0; // Pure virtual function
};

// Concrete Specification for size
class SizeSpecification : public Specification<Product<std::string>> {
private:
    std::string size;

public:
    SizeSpecification(const std::string& s) : size(s) {}
    bool isSatisfied(const std::shared_ptr<Product<std::string>>& product) const override {
        return product->getSpecification() == size;
    }
};
template<class  T>
class AndSpecification : public Specification<T>  {
  Specification<T>& first;
  Specification<T>& second;
  
  AndSpecification(Specification<T>& first ,Specification<T>& second):first(first),second(second){

  }
  virtual bool isSatisfied(const std::shared_ptr<T>& product) const  override{

    return first.isSatisfied(product)&second.isSatisfied(product);
  }

};

// Concrete Product class: House
class House : public Product<std::string> {
private:
    std::string size;

public:
    House(const std::string& n, const std::string& s) : Product(n), size(s) {}
    std::string getSpecification() const override {
        return size;
    }
    std::string getName() const override {
        return name;
    }
};

// Concrete Product class: Car
class Car : public Product<std::string> {
private:
    std::string size;

public:
    Car(const std::string& n, const std::string& s) : Product(n), size(s) {}
    std::string getSpecification() const override {
        return size;
    }
    std::string getName() const override {
        return name;
    }
};

// Templatized ProductFilter class
template <typename T>
class ProductFilter {
public:
    std::vector<std::shared_ptr<Product<T>>> filter(const std::vector<std::shared_ptr<Product<T>>>& products, const Specification<Product<T>>& spec) {
        std::vector<std::shared_ptr<Product<T>>> filteredProducts;
        for (const auto& product : products) {
            if (spec.isSatisfied(product)) {
                filteredProducts.push_back(product);
            }
        }
        return filteredProducts;
    }
};

int main() {
    std::vector<std::shared_ptr<Product<std::string>>> products;
    products.push_back(std::make_shared<House>("My Small House", "Small"));
    products.push_back(std::make_shared<House>("Cozy Medium House", "Medium"));
    products.push_back(std::make_shared<Car>("Luxury Large Car", "Large"));

    SizeSpecification largeSpec("Large");
    ProductFilter<std::string> filter;
    auto largeProducts = filter.filter(products, largeSpec);

    std::cout << "Filtered Large Products:" << std::endl;
    for (const auto& product : largeProducts) {
        std::cout << "- " << product->getName() << std::endl;
    }

    return 0;
}
