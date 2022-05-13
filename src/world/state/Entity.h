#ifndef ARCH_ROGUELIKE_ENTITY_H
#define ARCH_ROGUELIKE_ENTITY_H

#include <any>
#include <optional>
#include <string>
#include <map>

namespace world::state {
// Class for simulating behaviour of languages with runtime typing. Requested for suitable holding of properties.
class Entity {
  public:
    const std::map<std::string, std::any>& getAllProperties() const;
    std::optional<std::any> getProperty(const std::string& property_name) const;
    void setProperty(const std::string& property_name, std::any value);
    void deleteProperty(const std::string& property_name);

  protected:
    static bool compareTwoAny(const std::any& lhs, const std::any& rhs) ;

  private:
    std::map<std::string, std::any> property_;

};
}

#endif //ARCH_ROGUELIKE_ENTITY_H
