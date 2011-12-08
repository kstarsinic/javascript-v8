#ifndef _V8Context_h_
#define _V8Context_h_

#include <EXTERN.h>
#include <perl.h>
#undef New
#undef Null

#include <vector>
#include <map>
#include <string>

#include <v8.h>

using namespace v8;
using namespace std;

typedef map<string, Persistent<Object> > ObjectMap;

class V8Context {
    public:
        V8Context(int time_limit = 0);
        ~V8Context();

        void bind(const char*, SV*);
        SV* eval(SV*);

        Handle<Value> sv2v8(SV*);
        SV*           v82sv(Handle<Value>);

        Persistent<Context> context;
    private:
        Handle<Value>    rv2v8(SV*);
        Handle<Array>    av2array(AV*);
        Handle<Object>   hv2object(HV*);
        Handle<Function> cv2function(CV*);
        Handle<String>   sv2v8str(SV* sv);
        Handle<Object>   blessed2object(SV *sv);

        SV* array2sv(Handle<Array>);
        SV* object2sv(Handle<Object>);
        SV* object2blessed(Handle<Object>);
        SV* function2sv(Handle<Function>);

        void fill_prototype(Handle<Object> prototype, HV* stash);

        ObjectMap prototypes;

        int time_limit_;
};

#endif

