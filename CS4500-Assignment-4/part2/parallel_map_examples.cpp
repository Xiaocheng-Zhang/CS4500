#include "../column.h"
#include "../helper.h"
#include "../schema.h"
#include "../vec.h"
#include "../part1/dataframe.h"

void test() {
    Schema *schema = new Schema();
    DataFrame *df = new DataFrame(*schema);
    Column *col0 = new StringColumn(5, new String("Tom"), new String("Dave"),
                        new String("Allan"), new String("Joshua"), new String("Timothy"));
    Column *col1 = new IntColumn(5, 3, 4, 5, 6, 7);
    Column *col2 = new BoolColumn(5, true, false, true, false, false);
    Column *col3 = new FloatColumn(5, float(175.2), float(173.8), float(184.1), float(181.7), float(178.2));
    Column *col4 = new IntColumn(5, 22, 19, 18, 23, 24);
    Column *col5 = new StringColumn(5, new String("Bryant"), new String("Hoffman"),
                        new String("Lahm"), new String("Kroos"), new String("Alba"));
    Column *col6 = new BoolColumn(5, false, false, false, true, false);
    df->add_column(col0, new String("first_name"));
    df->add_column(col1, new String("first_name_length"));
    df->add_column(col2, new String("is_married"));
    df->add_column(col3, new String("height"));
    df->add_column(col4, new String("age"));
    df->add_column(col5, new String("last_name"));
    df->add_column(col6, new String("is_retired"));
}
