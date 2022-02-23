//
// Created by skybcyang on 2021/11/13.
//

#ifndef TEMPO_OFFLINE_REGISTER_H
#define TEMPO_OFFLINE_REGISTER_H

struct ITest;

using TestFactory = GeneralFactory<ITest, std::string>;
#define REGISTER_TEST_BY_NAME(_cls_name, _cls) \
    static int g_test_##_cls_name##cls = TestFactory::Instance().Register<_cls>(#_cls_name)
#define REGISTER_TEST(_cls) \
    REGISTER_TEST_BY_NAME(_cls, _cls)

#endif //TEMPO_OFFLINE_REGISTER_H
