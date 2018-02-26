#ifndef CMAKE_ENTITY_H
#define CMAKE_ENTITY_H

#include <gsl/gsl>
#include <memory>

namespace cm {
struct attribute {
  unsigned int strength = 0;
  unsigned int agility  = 0;
  unsigned int mental   = 0;
};

class weapon {
public:
  unsigned int attack(attribute const& attr) const;
};

class entity {
public:
  entity(attribute attr);
  unsigned int attack() const;
  void grab_weapon(gsl::not_null<weapon*> arm);

private:
  std::unique_ptr<weapon> arm;
  attribute attr;
};

} // namespace cm

#endif /* CMAKE_ENTITY_H */
