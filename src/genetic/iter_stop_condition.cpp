#include <genetic/iter_stop_condition.h>
#include <genetic/packer.h>

IterStopCondition::IterStopCondition(size_t iter_count):
    iter_count_{iter_count} {}


bool IterStopCondition::is_stop(const Packer &packer) const
{
    return packer.get_iteration_count() >= iter_count_;
}
