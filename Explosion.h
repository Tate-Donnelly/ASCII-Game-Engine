#include "Object.h"
namespace df {

    class Explosion : public Object {

    private:
        //void out();

    public:
        Explosion();
        int eventHandler(const Event* p_e) override;
    };
}