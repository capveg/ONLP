/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * SFF Utility for eeprom files.
 *
 ***********************************************************/
#include <sff/sff_config.h>

#if SFF_CONFIG_INCLUDE_SFF_TOOL == 1

#include <sff/sff.h>
#include <unistd.h>
#include <BigList/biglist.h>
#include <limits.h>

int
sff_tool(int argc, char* argv[])
{
    int rv = 0;
    int i;
    int c;

    int s = 0;
    int e = 0;
    int help = 0;
    int n = 0;
    int v = 0;

    biglist_t* fnames=NULL;


    while( (c = getopt(argc, argv, "sehnv")) != -1) {
        switch(c)
            {
            case 's': s = 1; break;
            case 'e': e = 1; break;
            case 'h': help=1; rv=0; break;
            case 'n': n=1; break;
            case 'v': v=1; break;
            default: help=1; rv = 1; break;
            }
    }

    if(help) {
        printf("Usage: %s [OPTIONS] [FILES]\n", argv[0]);
        printf("  -s    Read filenames from stdin. \n");
        printf("  -n    Print the filename if successful.\n");
        printf("  -v    Print the filename always.\n");
        printf("  -e    Show the raw eeprom data.\n");
        printf("  -h    Help.\n");
        return rv;
    }

    if(s) {
        /* Read filenames from stdin */
        char b[PATH_MAX];
        char* l;
        while((l = fgets(b, PATH_MAX, stdin))) {
            int len=SFF_STRLEN(l);
            if(len) {
                if(l[len-1] == '\n') {
                    l[len-1] = 0;
                }
                fnames = biglist_append(fnames, aim_strdup(l));
            }
        }
    }

    /* Read from command line. This can be used together with -s */
    for(i = optind; i < argc; i++) {
        fnames = biglist_append(fnames, aim_strdup(argv[i]));
    }

    biglist_t* ble;
    char* f;
    BIGLIST_FOREACH_DATA(ble, fnames, char*, f) {
        sff_info_t info;
        memset(&info, 0, sizeof(info));
        if( (rv = sff_info_init_file(&info, f)) >= 0) {
            if(n || v) {
                aim_printf(&aim_pvs_stdout, "%s\n", f);
            }
            if(e) {
                aim_printf(&aim_pvs_stdout, "eeprom:\n%{data}\n", info.eeprom, sizeof(info.eeprom));
            }
            sff_info_show(&info, &aim_pvs_stdout);
        }
        else if(v) {
            aim_printf(&aim_pvs_stdout, "%s: failed.\n", f);
        }
    }
    return 0;
}

#else
int __not_empty__;
#endif



