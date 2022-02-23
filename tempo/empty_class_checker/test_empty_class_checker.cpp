//
// Created by skybcyang on 2021/12/17.
//

#include "empty_class_checker.h"
#include "catch2/catch_test_macros.hpp"

struct XAction : ActionBase {
    virtual void exec() {}
};
struct YAction : ActionBase {
    virtual void exec() {}
};
struct ZAction : ActionBase {
    virtual void exec() {}
};
struct ZZAction : ZAction {
    virtual void exec() {}
};

DEFINE_ACTIONS_AGGREGATES(XYActions,
                          XAction, YAction);
DEFINE_ACTIONS_AGGREGATES(ZAcitons,
                          ZZAction);
DEFINE_ACTIONS_AGGREGATES(EmptyActions);

DEFINE_ACTIONS_AGGREGATES(Acitons,
                          XYActions, ZAcitons, EmptyActions);

TEST_CASE("test empty class base") {
    Acitons actions;
    EmptyActions empty_actions;
}
