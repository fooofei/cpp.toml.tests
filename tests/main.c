

#ifdef WIN32
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#include "toml.h"



int main()
{

    FILE * f=0;
    toml_table_t * conf_root=0;
    int i;
    toml_array_t * tmp_ar;
    toml_table_t * tmp_tb;

    enum{err_buf_size=0x10,};
    char errbuf[err_buf_size];


    f = fopen("../simple_toml.toml", "rb");

    if (f)
    {

        conf_root = toml_parse_file(f, errbuf, err_buf_size);

        if (conf_root)
        {

            toml_table_t * ini_family = toml_table_in(conf_root, "family");
            if (ini_family)
            {
                const char * key = 0;
                const char * value = 0;

                for (i=0;;i+=1)
                {
                    key = toml_key_in(ini_family, i);
                    if (!key) break;
                    value = toml_raw_in(ini_family, key);
                    if (!value) value = "";
                    printf("family.%s=%s\n", key, value);
                }

                
                tmp_ar = toml_array_in(ini_family, "pets");
                if (tmp_ar)
                {
                    printf("family.perts=[");
                    for (i=0;;i+=1)
                    {
                        value = toml_raw_at(tmp_ar, i);
                        if (!value)
                        {
                            break;
                        }
                        printf("%s,",value);

                    }
                    printf("]\n");
                }

                tmp_ar = toml_array_in(ini_family, "kids");
                if (tmp_ar)
                {
                    printf("family.kids=[");
                    for (i=0;; i+=1)
                    {
                        tmp_tb = toml_table_at(tmp_ar, i);
                        if (!tmp_tb)break;

                        value = toml_raw_in(tmp_tb, "name");
                        printf("{name=%s, ", value);
                        value = toml_raw_in(tmp_tb, "age");
                        printf("age=%s},", value);
                    }

                    printf("]\n");
                }
            }

            toml_free(conf_root);
            conf_root = 0;
        }

        fclose(f);
        f = 0;
    }

    return 0;
}



