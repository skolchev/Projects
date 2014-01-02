using Gallery.Data;
using Gallery.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gallery.Repositories
{
    public class UnitOfWork : IDisposable
    {
        private GalleryContext context = new GalleryContext();
        private EfRepository<User> usersRepository;
        private EfRepository<Album> albumsRepository;
        private EfRepository<Image> imagesRepository;
        private EfRepository<Comment> commentsRepository;
        private EfRepository<Gallery.Models.Gallery> galleriesRepository;
        bool disposed;

        public EfRepository<User> UsersRepository
        {
            get
            {
                if (this.usersRepository == null)
                {
                    this.usersRepository = new EfRepository<User>(context);
                }

                return this.usersRepository;
            }
        }

        public EfRepository<Gallery.Models.Gallery> GalleriesRepository
        {
            get
            {
                if (this.galleriesRepository == null)
                {
                    this.galleriesRepository = new EfRepository<Gallery.Models.Gallery>(context);
                }

                return this.galleriesRepository;
            }
        }

        public EfRepository<Album> AlbumsRepository
        {
            get
            {
                if (this.albumsRepository == null)
                {
                    this.albumsRepository = new EfRepository<Album>(context);
                }

                return this.albumsRepository;
            }
        }

        public EfRepository<Image> ImagesRepository
        {
            get
            {
                if (this.imagesRepository == null)
                {
                    this.imagesRepository = new EfRepository<Image>(context);
                }

                return this.imagesRepository;
            }
        }

        public EfRepository<Comment> CommentsRepository
        {
            get
            {
                if (this.commentsRepository == null)
                {
                    this.commentsRepository = new EfRepository<Comment>(context);
                }

                return this.commentsRepository;
            }
        }

        public void Save()
        {
            this.context.SaveChanges();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!this.disposed)
            {
                if (disposing)
                {
                    context.Dispose();
                }
            }
            this.disposed = true;
        }
    }
}
