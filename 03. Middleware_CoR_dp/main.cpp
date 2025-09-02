#include "middleware/router/MiddlewareRouter.h"
#include "middleware/matchers/PathPrefixMatcher.h"
#include "middleware/matchers/MethodMatcher.h"
#include "middleware/matchers/HeaderMatcher.h"
#include "middleware/factories/StaticChainFactory.h"
#include "middleware/factories/ApiChainFactory.h"
#include "middleware/factories/AdminChainFactory.h"
#include "middleware/handlers/SimpleHandler.h"
#include "middleware/entities/Request.h"
#include "middleware/entities/Response.h"
#include <middleware/factories/FactoryType.h>

#include <iostream>
#include <memory>

using namespace std;

int main() {
    MiddlewareRouter router;

    // Register rules — order matters: more specific rules first
    router.addRule("api",   make_unique<PathPrefixMatcher>("/api"),   make_unique<ApiChainFactory>());
    router.addRule("admin", make_unique<PathPrefixMatcher>("/admin"), FactoryType::Admin);
    router.addRule("static",make_unique<PathPrefixMatcher>("/"),      make_unique<StaticChainFactory>());

    // 1) request to API (authorized)
    {
        auto r1 = make_unique<Request>();
        r1->path = "/api/data";
        r1->method = "GET";
        r1->headers["Authorization"] = "Bearer valid-token";

        auto res1 = make_unique<Response>();
        router.route(r1.get(), res1.get());
        cout << "Response1: " << res1->status << " " << res1->body << endl;
    }

    // 2) request to API (unauthorized)
    {
        auto r2 = make_unique<Request>();
        r2->path = "/api/data";
        r2->method = "GET";

        auto res2 = make_unique<Response>();
        router.route(r2.get(), res2.get());
        cout << "Response2: " << res2->status << " " << res2->body << endl;
    }

    // 3) request to static content (catch-all chain)
    {
        auto r3 = make_unique<Request>();
        r3->path = "/index.html";
        r3->method = "GET";

        auto res3 = make_unique<Response>();
        router.route(r3.get(), res3.get());
        cout << "Response3: " << res3->status << " " << res3->body << endl;
    }

    // 4) dynamically insert a SimpleHandler after the "Logging" handler in the "api" chain
    router.insertAfter("api", "Logging", make_unique<SimpleHandler>("ExtraLogger"));

    // send the same authorized API request again to observe the inserted handler
    {
        auto r4 = make_unique<Request>();
        r4->path = "/api/data";
        r4->method = "GET";
        r4->headers["Authorization"] = "Bearer valid-token";

        auto res4 = make_unique<Response>();
        router.route(r4.get(), res4.get());
        cout << "Response4: " << res4->status << " " << res4->body << endl;
    }

    // 5) remove Compression handler from api chain (if present)
    router.removeHandler("api", "Compression");

    // send the API request again
    {
        auto r5 = make_unique<Request>();
        r5->path = "/api/data";
        r5->method = "GET";
        r5->headers["Authorization"] = "Bearer valid-token";

        auto res5 = make_unique<Response>();
        router.route(r5.get(), res5.get());
        cout << "Response5: " << res5->status << " " << res5->body << endl;
        // Note: Compression was removed, so header "Content-Encoding" will not be added by CompressionHandler anymore.
    }

    // 6) admin panel request with auth
    {
        auto r6 = make_unique<Request>();
        r6->path = "/admin/panel";
        r6->method = "GET";
        r6->headers["Authorization"] = "Bearer valid-token";

        auto res6 = make_unique<Response>();
        router.route(r6.get(), res6.get());
        cout << "Admin response (with token): " << res6->status << " " << res6->body << endl;
    }

    // 7) admin panel request without auth
    {
        auto r7 = make_unique<Request>();
        r7->path = "/admin/panel";
        r7->method = "GET";

        auto res7 = make_unique<Response>();
        router.route(r7.get(), res7.get());
        cout << "Admin response (no token): " << res7->status << " " << res7->body << endl;
    }

    return 0;
}