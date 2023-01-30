//
// Created by skybcyang on 2022/7/16.
//

#ifndef SNIPPETS_META_INFO_H
#define SNIPPETS_META_INFO_H

#define DATA_META_TABLE(table_name) \
enum class tablename

DATA_META_TABLE(table1) {
    DATA_META_START(table_start)
    DATA_META_FIELD(table_field)
    DATA_META_END()
};

#endif //SNIPPETS_META_INFO_H
