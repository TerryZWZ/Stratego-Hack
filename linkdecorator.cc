#include "linkdecorator.h"

LinkDecorator::LinkDecorator(shared_ptr<Link> component) : Link(*component), component {component} {}
