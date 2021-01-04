using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab9_MAP.model;
using Lab9_MAP.validator;

namespace Lab9_MAP.repository
{
    public delegate E CreateEntity<E>(string line);

    abstract class InFileRepository<ID, E> : InMemoryRepository<ID, E> where E:Entity<ID>
    {
        protected string fileName;
        protected CreateEntity<E> createEntity;

        public InFileRepository(IValidator<E> val, String fileName, CreateEntity<E> createEntity) : base(val)
        {
            this.fileName = fileName;
            this.createEntity = createEntity;
            if (createEntity != null)
                loadFromFile();
        }

        protected virtual void loadFromFile()
        {
            List<E> list = DataReader.ReadData(fileName, createEntity);
            list.ForEach(x => entities[x.ID] = x);
        }
    }
}
