//
// Created by skybcyang on 2022/7/16.
//

#ifndef SNIPPETS_META_INFO_H
#define SNIPPETS_META_INFO_H

// X-Macro pattern for defining data meta information
#define DATA_META_START(name) name,
#define DATA_META_FIELD(name) name,
#define DATA_META_END()

#define DATA_META_TABLE(table_name) \
    enum class table_name

DATA_META_TABLE(table1) {
    DATA_META_START(table_start)
    DATA_META_FIELD(table_field)
    DATA_META_END()
};

#endif //SNIPPETS_META_INFO_H
