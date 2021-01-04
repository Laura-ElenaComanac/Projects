using Lab9_MAP.model;
using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.repository
{
    interface IRepository<ID, E> where E:Entity<ID>
    {
        E FindOne(ID id);
        IEnumerable<E> FindAll();
        E Save(E entity);
        E Delete(ID id);
        E Update(E entity);
    }
}
