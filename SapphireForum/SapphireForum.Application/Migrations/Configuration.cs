namespace SapphireForum.Application.Migrations
{
    using Microsoft.AspNet.Identity;
    using Microsoft.AspNet.Identity.EntityFramework;
    using Microsoft.AspNet.Identity.Owin;
    using SapphireForum.Application.Models;
    using System;
    using System.Data.Entity;
    using System.Data.Entity.Migrations;
    using System.Linq;

    internal sealed class Configuration : DbMigrationsConfiguration<SapphireForum.Application.Models.ApplicationDbContext>
    {
        public Configuration()
        {
            this.AutomaticMigrationsEnabled = true;
            this.AutomaticMigrationDataLossAllowed = true;
        }

        protected override void Seed(SapphireForum.Application.Models.ApplicationDbContext context)
        {
            //  This method will be called after migrating to the latest version.

            //  You can use the DbSet<T>.AddOrUpdate() helper extension method 
            //  to avoid creating duplicate seed data. E.g.

            Role adminRole = new Role { Id = "1", Name = "Admin" };
            Role userRole = new Role { Id = "2", Name = "User" };
            context.Roles.AddOrUpdate(adminRole);
            context.Roles.AddOrUpdate(userRole);

            //Creating if doesn't exist
            ApplicationUser user = context.Users.FirstOrDefault(u => u.UserName == "admincho");
            if (user == null)
            {
                var manager = new AuthenticationIdentityManager(new IdentityStore(new ApplicationDbContext()));
                IdentityResult result = manager.Users.CreateLocalUser(new ApplicationUser() { UserName = "admincho" }, "admincho");
                context.SaveChanges();

                user = context.Users.FirstOrDefault(u => u.UserName == "admincho");

                //Assigning Admin role to admincho
                UserRole userRoleAdmin = new UserRole()
                {
                    RoleId = "1",
                    UserId = user.Id,
                };
                context.UserRoles.Add(userRoleAdmin);

                //Assigning User role to admincho
                UserRole userRoleUser = new UserRole()
                {
                    RoleId = "2",
                    UserId = user.Id,
                };
                context.UserRoles.Add(userRoleUser);
                context.SaveChanges();
            }
        }
    }
}
