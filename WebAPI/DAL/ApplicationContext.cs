using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using SmartHome.Models;

namespace SmartHome.DAL
{
    public partial class ApplicationContext : DbContext
    {
        public ApplicationContext(DbContextOptions<ApplicationContext> options)
            : base(options)
        { }

        // protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        // {
        //     #warning To protect potentially sensitive information in your connection string, you should move it out of source code. See http://go.microsoft.com/fwlink/?LinkId=723263 for guidance on storing connection strings.
        //     optionsBuilder.UseSqlServer(@"Server=tcp:smart-home-hub.database.windows.net,1433;Initial Catalog=smart-home;Persist Security Info=False;User ID=drepac;Password=vxjv.45Q;MultipleActiveResultSets=False;Encrypt=True;TrustServerCertificate=False;Connection Timeout=30;");
        // }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Gas>(entity =>
            {
                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.Co).HasColumnName("CO");

                entity.Property(e => e.Co2).HasColumnName("CO2");

                entity.Property(e => e.Gas1).HasColumnName("Gas");

                entity.Property(e => e.MeasuredAt).HasColumnType("datetime");
            });

            modelBuilder.Entity<Moisture>(entity =>
            {
                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.MeasuredAt).HasColumnType("datetime");

                entity.Property(e => e.Moisture1).HasColumnName("Moisture");
            });

            modelBuilder.Entity<MovementSensor>(entity =>
            {
                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.MovementDetected).HasColumnType("datetime");
            });

            modelBuilder.Entity<Temperature>(entity =>
            {
                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.MeasuredAt).HasColumnType("datetime");
            });

            modelBuilder.Entity<WaterLevel>(entity =>
            {
                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.MeasuredAt).HasColumnType("datetime");
            });
        }

        public virtual DbSet<Gas> Gas { get; set; }
        public virtual DbSet<Moisture> Moisture { get; set; }
        public virtual DbSet<MovementSensor> MovementSensor { get; set; }
        public virtual DbSet<Temperature> Temperature { get; set; }
        public virtual DbSet<WaterLevel> WaterLevel { get; set; }
    }
}