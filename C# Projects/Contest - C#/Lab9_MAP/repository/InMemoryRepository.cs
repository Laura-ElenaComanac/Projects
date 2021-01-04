using Lab9_MAP.model;
using Lab9_MAP.repository;
using Lab9_MAP.validator;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab9_MAP.repository
{
    class InMemoryRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
    {
        protected IValidator<E> val;

        protected IDictionary<ID, E> entities = new Dictionary<ID, E>();

        public InMemoryRepository(IValidator<E> validator)
        {
            this.val = validator;
        }

        public E Delete(ID id)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<E> FindAll()
        {
            return entities.Values.ToList<E>();
        }

        public E FindOne(ID id)
        {
            throw new NotImplementedException();
        }

        public E Save(E entity)
        {
            if (entity == null)
                throw new ArgumentNullException("Entitatea nu poate fi nula!");
            this.val.Validate(entity);
            if (this.entities.ContainsKey(entity.ID))
            {
                return entity;
            }
            this.entities[entity.ID] = entity;
            return default(E);
        }

        public E Update(E entity)
        {
            throw new NotImplementedException();
        }
    }
}
