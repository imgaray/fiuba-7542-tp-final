#include "TabAdminConfig.h"

TabAdminConfig::TabAdminConfig(BaseObjectType* cobject,
            const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::VBox(cobject), Buildable(_builder) {}

TabAdminConfig::~TabAdminConfig() {}
