using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(SapphireForum.Application.Startup))]
namespace SapphireForum.Application
{
    public partial class Startup {
        public void Configuration(IAppBuilder app) {
            ConfigureAuth(app);
        }
    }
}
