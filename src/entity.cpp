#include "entity.h"

using namespace cm;

entity::entity(attribute _attr) : attr(_attr) {}

void entity::grab_weapon(gsl::not_null<weapon*> _arm) { arm.reset(_arm); }

unsigned int entity::attack() const { return arm->attack(attr); }

unsigned int weapon::attack(attribute const& attr) const {
  return 5 * attr.strength;
}
